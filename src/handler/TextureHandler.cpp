#include "TextureHandler.h"
#include "BundleAssetsHandler.h"
#include <SDL3_image/SDL_image.h>

#include <vector>

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

// --- TextureManager Implementierung ---
std::unordered_map<std::string, Texture *> TextureManager::textures;

void TextureManager::Add(SDL_Renderer &renderer, const std::string &id, const std::string &filename)
{

    SDL_Surface *surface = IMG_Load(filename.c_str());
    if (!surface)
    {
        std::cerr << "IMG_Load Fehler: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture *sdlTex = SDL_CreateTextureFromSurface(&renderer, surface);
    int w = surface->w;
    int h = surface->h;
    SDL_DestroySurface(surface);

    if (!sdlTex)
    {
        std::cerr << "SDL_CreateTextureFromSurface Fehler: " << SDL_GetError() << std::endl;
        return;
    }

    textures[id] = new Texture(sdlTex, w, h);
}

SDL_Texture *TextureManager::loadTextureFromBundle(SDL_Renderer *renderer, const std::string &fullPathInBundle)
{
    std::vector<uint8_t> data = BundleAssetsHandler::getFileData(fullPathInBundle);
    if (data.empty())
    {
        return nullptr;
    }

    SDL_IOStream *io = SDL_IOFromConstMem(data.data(), static_cast<int>(data.size()));
    if (!io)
    {
        return nullptr;
    }

    SDL_Texture *texture = IMG_LoadTexture_IO(renderer, io, true); // true = IOStream close
    if (!texture)
    {
        std::cerr << "IMG_LoadTexture_IO error: " << SDL_GetError() << "\n";
    }
    return texture;
}

SDL_Texture *TextureManager::Get(const std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return it->second->tex;
    }
    return nullptr;
}

std::pair<int, int> TextureManager::GetSize(const std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return {it->second->width, it->second->height};
    }
    return {0, 0};
}

void TextureManager::Delete(const std::string &id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        delete it->second;
        textures.erase(it);
    }
}

void TextureManager::ClearAll()
{
    for (auto &pair : textures)
    {
        delete pair.second;
    }
    textures.clear();
}

void TextureManager::InitPlaceholder(SDL_Renderer *renderer)
{
    // 2x2 RGBA-Textur trans
    const int w = 2;
    const int h = 2;
    Uint32 pixels[w * h] = {
        0x00000000, 0x00000000,
        0x00000000, 0x00000000};

    SDL_Surface *surface = SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_RGBA32, pixels, w * sizeof(Uint32));

    if (!surface)
    {
        std::cerr << "Failed to create placeholder surface: " << SDL_GetError() << "\n";
        return;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!tex)
    {
        std::cerr << "Failed to create placeholder texture: " << SDL_GetError() << "\n";
        return;
    }

    textures["__placeholder__"] = new Texture(tex, w, h);
}
