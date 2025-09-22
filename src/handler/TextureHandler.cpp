#include "TextureHandler.h"

// --- Texture Implementierung ---
Texture::Texture(SDL_Texture* t, int w, int h)
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
std::unordered_map<std::string, Texture*> TextureManager::textures;

void TextureManager::Add(SDL_Renderer& renderer, const std::string& id, const std::string& filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface)
    {
        std::cerr << "IMG_Load Fehler: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(&renderer, surface);
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

SDL_Texture* TextureManager::Get(const std::string& id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return it->second->tex;
    }
    return nullptr;
}

std::pair<int,int> TextureManager::GetSize(const std::string& id)
{
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return {it->second->width, it->second->height};
    }
    return {0, 0};
}

void TextureManager::Delete(const std::string& id)
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
    for (auto& pair : textures)
    {
        delete pair.second;
    }
    textures.clear();
}
