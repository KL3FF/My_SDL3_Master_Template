#include "TextureHandler.h"
#include "AppWindow.h"
#include "WindowConfig.h"
#include "BundleAssetsHandler.h"
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <unordered_set>


// All loaded textures
std::unordered_map<std::string, Texture *> TextureManager::textures;

// Queue for textures that should be loaded
std::queue<std::pair<std::string, std::vector<std::string>>> TextureManager::textureLoadingQueue;

// Set for checking if a texture is already in the loading queue
std::unordered_set<std::string> TextureManager::queueSet;

// Texture implementation
Texture::Texture(SDL_Texture *t, int w, int h)
    : tex(t), width(w), height(h) {}

Texture::~Texture()
{
    if (tex)
    {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }
}

// Adds a texture to the manager if it doesn't already exist
void TextureManager::AddTextureInternal(SDL_Renderer &renderer,  std::string &id, std::vector<std::string> &paths)
{
    // Check if texture already exists
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return;
    }


    size_t index = static_cast<size_t>(WindowConfig::getTextureQuality());
    if (index >= paths.size())
    {
        index = paths.size() - 1;
    }

    for (int i = static_cast<int>(index); i >= 0; --i)
    {
        // Load texture data from bundle
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
      
        // SDL functions expect a pointer, so use &renderer
        SDL_Texture *texture = IMG_LoadTexture_IO(&renderer, io, true);
        if (!texture)
        {
            std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << "\n";
            continue;
        }
        // Store the texture in the manager
        textures[id] = new Texture(texture, texture->w, texture->h);
        return;
    }


    // No Tex found => backup emptyTexture
    SDL_Texture *tex = EmptyTexture(renderer);
    if (!tex)
    {
        return;
    }
    textures[id] = new Texture(tex, 2, 2);
}

// Returns the SDL_Texture pointer for a given id, or a placeholder if not loaded yet
SDL_Texture *TextureManager::GetTextureInternal(const std::string &id, std::vector<std::string> &paths)
{

    // Search for texture and return it if found
    auto it = textures.find(id);
    if (it != textures.end())
    {
     
        return it->second->tex;
    }
    else
    {
        // If not found, check if it's already in the loading queue
        auto it = queueSet.find(id);
        if (it == queueSet.end())
        {
            // Add to loading queue if not already present
            textureLoadingQueue.push({id, paths});
            queueSet.insert(id);
        }

        // Return placeholder texture if available
        auto placeholder = textures.find("__placeholder__");
        if (placeholder != textures.end())
        {
            std::cout<< "Placeholder" << "\n";
            return placeholder->second->tex;
        }

        // No texture available
        return nullptr;
    }
    return nullptr;
}

// Returns the size (width, height) of a texture, or (0, 0) if not found
std::pair<int, int> TextureManager::GetSize(std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return {it->second->width, it->second->height};
    }

    return {0, 0};
}

// Deletes a texture from the manager and frees its memory
void TextureManager::DeleteTexture(std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        delete it->second;
        textures.erase(it);
    }
}

// Deletes all textures and clears the manager
void TextureManager::ClearAll()
{
    for (auto &pair : textures)
    {
        delete pair.second;
    }

    textures.clear();
}

// Creates and stores a minimal placeholder texture (used when requested texture is not loaded yet)
void TextureManager::InitPlaceholder(SDL_Renderer &renderer)
{
    SDL_Texture *tex = EmptyTexture(renderer);
    if (!tex)
    {
        return;
    }
    textures["__placeholder__"] = new Texture(tex, 2, 2);
}

SDL_Texture *TextureManager::EmptyTexture(SDL_Renderer &renderer)
{

    constexpr int  w = 2; 
    constexpr int h = 2;
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

// Loads the next texture in the loading queue (should be called regularly, e.g. once per frame)
void TextureManager::TextureLazyLoad(SDL_Renderer &renderer)
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

// Unloads textures that are no longer needed (not implemented yet)
void TextureManager::TextureProcessUnload()
{

    // Not implemented yet
}
