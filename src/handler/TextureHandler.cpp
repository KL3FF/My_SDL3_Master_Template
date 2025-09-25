#include "TextureHandler.h"
#include "BundleAssetsHandler.h"
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <unordered_set>

// All loaded textures
std::unordered_map<std::string, Texture *> TextureManager::textures;

// Queue for textures that should be loaded
std::queue<std::string> TextureManager::textureLoadingQueue;

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
void TextureManager::AddTexture(SDL_Renderer &renderer, const std::string &id)
{
    // Check if texture already exists
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return;
    }

    // Load texture data from bundle
    std::vector<uint8_t> data = BundleAssetsHandler::GetFileData(id);
    if (data.empty())
    {
        return;
    }

    // Create SDL IO stream from memory
    SDL_IOStream *io = SDL_IOFromConstMem(data.data(), static_cast<int>(data.size()));
    if (!io)
    {
        return;
    }
    // SDL functions expect a pointer, so use &renderer
    SDL_Texture *texture = IMG_LoadTexture_IO(&renderer, io, true);
    if (!texture)
    {
        std::cerr << "IMG_LoadTexture_IO error: " << SDL_GetError() << "\n";
        return;
    }

    // Store the texture in the manager
    textures[id] = new Texture(texture, texture->w, texture->h);
}

// Returns the SDL_Texture pointer for a given id, or a placeholder if not loaded yet
SDL_Texture *TextureManager::GetTexture(const std::string &id)
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
            textureLoadingQueue.push(id);
            queueSet.insert(id);
        }

        // Return placeholder texture if available
        auto placeholder = textures.find("__placeholder__");
        if (placeholder != textures.end())
        {
            return placeholder->second->tex;
        }

        // No texture available
        return nullptr;
    }

    return nullptr;
}

// Returns the size (width, height) of a texture, or (0, 0) if not found
std::pair<int, int> TextureManager::GetSize(const std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return {it->second->width, it->second->height};
    }

    return {0, 0};
}

// Deletes a texture from the manager and frees its memory
void TextureManager::DeleteTexture(const std::string &id)
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
    const int w = 2;
    const int h = 2;
    Uint32 pixels[w * h] = {
        0x00000000, 0x00000000,
        0x00000000, 0x00000000};

    // Create a 2x2 transparent surface
    SDL_Surface *surface = SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_RGBA32, pixels, w * sizeof(Uint32));
    if (!surface)
    {
        std::cerr << "Failed to create placeholder surface: " << SDL_GetError() << "\n";
        return;
    }

    // Create a texture from the surface
    SDL_Texture *tex = SDL_CreateTextureFromSurface(&renderer, surface);
    SDL_DestroySurface(surface);

    if (!tex)
    {
        std::cerr << "Failed to create placeholder texture: " << SDL_GetError() << "\n";
        return;
    }

    // Store the placeholder texture
    textures["__placeholder__"] = new Texture(tex, w, h);
}

// Loads the next texture in the loading queue (should be called regularly, e.g. once per frame)
void TextureManager::TextureProcessLoad(SDL_Renderer &renderer)
{
    if (!textureLoadingQueue.empty())
    {
        const std::string filename = textureLoadingQueue.front();
        TextureManager::AddTexture(renderer, filename);
        textureLoadingQueue.pop();
        queueSet.erase(filename);
    }
}

// Unloads textures that are no longer needed (not implemented yet)
void TextureManager::TextureProcessUnload()
{
    // Not implemented yet
}
