#include "TextureHandler.h"
#include "BundleAssetsHandler.h"
#include <SDL3_image/SDL_image.h>
#include <vector>

std::unordered_map<std::string, Texture *> TextureManager::textures;
std::queue<std::string> TextureManager::textureLoadingQueue;

// --- Texture Implementierung ---
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

// --- Add Funktion ---
void TextureManager::Add(SDL_Renderer &renderer, const std::string &fullPathInBundle)
{
    // Textur existiert bereits
    if (textures.find(fullPathInBundle) != textures.end())
        return;

    std::vector<uint8_t> data = BundleAssetsHandler::GetFileData(fullPathInBundle);
    if (data.empty())
        return;

    SDL_IOStream *io = SDL_IOFromConstMem(data.data(), static_cast<int>(data.size()));
    if (!io)
        return;

    // SDL-Funktionen erwarten Pointer, daher &renderer
    SDL_Texture *texture = IMG_LoadTexture_IO(&renderer, io, true);
    if (!texture)
    {
        std::cerr << "IMG_LoadTexture_IO error: " << SDL_GetError() << "\n";
        return;
    }

    textures[fullPathInBundle] = new Texture(texture, texture->w, texture->h);
}

// --- Get Funktion ---
SDL_Texture *TextureManager::Get(const std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
        return it->second->tex;
    return nullptr;
}

// --- GetSize Funktion ---
std::pair<int, int> TextureManager::GetSize(const std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
        return {it->second->width, it->second->height};
    return {0, 0};
}

// --- Delete Funktion ---
void TextureManager::Delete(const std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        delete it->second;
        textures.erase(it);
    }
}

// --- ClearAll Funktion ---
void TextureManager::ClearAll()
{
    for (auto &pair : textures)
        delete pair.second;
    textures.clear();
}

// --- InitPlaceholder Funktion ---
void TextureManager::InitPlaceholder(SDL_Renderer &renderer)
{
    const int w = 2;
    const int h = 2;
    Uint32 pixels[w * h] = {
        0x00000000, 0x00000000,
        0x00000000, 0x00000000
    };

    SDL_Surface *surface = SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_RGBA32, pixels, w * sizeof(Uint32));
    if (!surface)
    {
        std::cerr << "Failed to create placeholder surface: " << SDL_GetError() << "\n";
        return;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(&renderer, surface);
    SDL_DestroySurface(surface);

    if (!tex)
    {
        std::cerr << "Failed to create placeholder texture: " << SDL_GetError() << "\n";
        return;
    }

    textures["__placeholder__"] = new Texture(tex, w, h);
}

// --- TextureProcessLoad Funktion ---
void TextureManager::TextureProcessLoad(SDL_Renderer &renderer)
{
    if (!textureLoadingQueue.empty())
    {
        const std::string filename = textureLoadingQueue.front();
        TextureManager::Add(renderer, filename);
        textureLoadingQueue.pop();
    }
}

// --- TextureProcessUnload Funktion ---
void TextureManager::TextureProcessUnload()
{
    // noch leer
}
