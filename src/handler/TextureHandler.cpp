#include "TextureHandler.h"
#include "AppWindow.h"
#include "WindowConfig.h"
#include "BundleAssetsHandler.h"
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <unordered_set>

// Static members
std::unordered_map<std::string, Texture *> TextureManager::textures;
std::unordered_map<std::string, Texture *>::iterator TextureManager::currentIt = TextureManager::textures.end();
std::queue<std::pair<std::string, std::vector<std::string>>> TextureManager::textureLoadingQueue;
std::unordered_set<std::string> TextureManager::queueSet;

// --- Texture implementation ---
Texture::Texture(SDL_Texture *_tex, int _width, int _height, int _ttl, bool _persistent)
    : tex(_tex), width(_width), height(_height), ttl(_ttl), persistent(_persistent) {}

Texture::~Texture()
{
    if (tex)
    {
        SDL_DestroyTexture(tex); // Free the SDL texture
        tex = nullptr;
    }
}

int Texture::GetTTL() { return ttl; }
void Texture::SetTTL(int _ttl) { ttl = _ttl; }
bool Texture::GetPersistent() { return persistent; }
void Texture::SetPersistent(bool _persistent) { persistent = _persistent; }

// --- TextureManager functions ---

// Add a texture to the manager if it doesn't exist yet
void TextureManager::AddTextureInternal(SDL_Renderer &renderer, std::string &id, std::vector<std::string> &paths)
{
    // Return if texture already exists
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return;
    }

    // Determine which quality version to load
    size_t index = static_cast<size_t>(WindowConfig::getTextureQuality());
    if (index >= paths.size())
        index = paths.size() - 1;

    // Try loading textures from high to low quality
    for (int i = static_cast<int>(index); i >= 0; --i)
    {
        // Get file data from bundle
        std::vector<uint8_t> data = BundleAssetsHandler::GetFileData({paths[i]});
        if (data.empty())
        {
            continue;
        }

        // Create SDL IO stream from memory
        SDL_IOStream *io = SDL_IOFromConstMem(data.data(), static_cast<int>(data.size()));
        if (!io)
        {
            continue;
        }

        // Load texture from SDL IO stream
        SDL_Texture *texture = IMG_LoadTexture_IO(&renderer, io, true);
        if (!texture)
        {
            std::cerr << "Failed to create texture: " << SDL_GetError() << "\n";
            continue;
        }

        // Store loaded texture
        textures[id] = new Texture(texture, texture->w, texture->h, maxTTL, false);
        return;
    }

    // If no texture could be loaded, create a minimal fallback
    SDL_Texture *tex = EmptyTexture(renderer);
    if (!tex)
    {
        return;
    }
    textures[id] = new Texture(tex, 2, 2, maxTTL, false);
}

// Return texture pointer by ID, or placeholder if not loaded yet
SDL_Texture *TextureManager::GetTextureInternal(const std::string &id, std::vector<std::string> &paths)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        it->second->SetTTL(maxTTL);
        return it->second->tex;
    }

    if (!paths.empty())
    {
        // Queue texture for lazy loading if not already queued
        auto itQueue = queueSet.find(id);
        if (itQueue == queueSet.end())
        {
            textureLoadingQueue.push({id, paths});
            queueSet.insert(id);
        }
    }
    // Return placeholder if available
    auto placeholder = textures.find("__placeholder__");
    if (placeholder != textures.end())
    {
        // std::cout << "Placeholder" << "\n";
        return placeholder->second->tex;
    }

    return nullptr;
}

// Add a texture lazy to the manager if it doesn't exist yet
void TextureManager::AddLazyTextureInternal(const std::string &id, std::vector<std::string> &paths)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return;
    }

    // Queue texture for lazy loading if not already queued
    auto itQueue = queueSet.find(id);
    if (itQueue == queueSet.end())
    {
        textureLoadingQueue.push({id, paths});
        queueSet.insert(id);
    }
}

// Return texture size (width, height)
std::pair<int, int> TextureManager::GetSize(std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return {it->second->width, it->second->height};
    }
    return {0, 0};
}

// Delete a texture and remove from manager
void TextureManager::DeleteTexture(std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        // Update iterator if pointing to this texture
        if (currentIt == it)
            currentIt = textures.erase(it);
        else
        {
            delete it->second;
            textures.erase(it);
        }

        // Adjust iterator after deletion
        if (textures.empty())
        {
            currentIt = textures.end();
        }
        else if (currentIt == textures.end())
        {
            currentIt = textures.begin();
        }
    }
}

// Clear all textures
void TextureManager::ClearAll()
{
    for (auto &pair : textures)
    {
        delete pair.second;
    }
    textures.clear();
    currentIt = textures.end();
}

// Initialize placeholder texture
void TextureManager::InitPlaceholder(SDL_Renderer &renderer)
{
    SDL_Texture *tex = EmptyTexture(renderer);
    if (!tex)
    {
        return;
    }
    textures["__placeholder__"] = new Texture(tex, 2, 2, maxTTL, true);
}

// Create minimal empty texture
SDL_Texture *TextureManager::EmptyTexture(SDL_Renderer &renderer)
{
    constexpr int w = 2, h = 2;
    Uint32 pixels[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

    SDL_Surface *surface = SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_RGBA32, pixels, w * sizeof(Uint32));
    if (!surface)
    {
        std::cerr << "Failed to create empty surface: " << SDL_GetError() << "\n";
        return nullptr;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(&renderer, surface);
    SDL_DestroySurface(surface);

    if (!tex)
    {
        std::cerr << "Failed to create empty texture: " << SDL_GetError() << "\n";
        return nullptr;
    }
    return tex;
}

// Lazy load the next texture in queue
void TextureManager::TextureLazyLoader(SDL_Renderer &renderer)
{
    if (!textureLoadingQueue.empty())
    {
        std::cout << "Load Texture with lazy loader" << "\n";
        auto [id, path] = textureLoadingQueue.front();
        textureLoadingQueue.pop();
        TextureManager::AddTextureInternal(renderer, id, path);

        queueSet.erase(id);
    }
}

// Process unloading textures with expired TTL
void TextureManager::TextureLazyUnloader()
{
    if (textures.empty())
    {
        currentIt = textures.end();
        return;
    }

    if (currentIt == textures.end())
    {
        currentIt = textures.begin();
    }

    // Skip persistent textures
    if (!currentIt->second->GetPersistent())
    {
        // Reduce TTL
        if (currentIt->second->GetTTL() == maxTTL)
        {
            currentIt->second->SetTTL(currentIt->second->GetTTL() - 1);
        }
        else
        {
            currentIt->second->SetTTL(currentIt->second->GetTTL() - textures.size());
        }

        // Delete if TTL expired
        if (currentIt->second->GetTTL() <= 0)
        {
            delete currentIt->second;
            currentIt = textures.erase(currentIt);
            if (textures.empty())
            {
                currentIt = textures.end();
            }
        }
        else
            ++currentIt;
    }
    else
        ++currentIt;

    if (currentIt == textures.end())
    {
        currentIt = textures.begin();
    }
}
