#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>
#include <queue>
#include <unordered_set>
#include "AppWindow.h"
#include "WindowConfig.h"
// Helper structure for textures
struct Texture
{
    SDL_Texture *tex;
    float ttl = 300; // Time to live in seconds
    int width;
    int height;

    Texture(SDL_Texture *t, int w, int h);
    ~Texture();
};

class TextureManager
{
public:
    // GetTexture a texture
    template <typename... stringVT>
    static SDL_Texture *GetTexture(const std::string &id, stringVT... paths)
    {
        std::vector<std::string> vecPaths = {paths...};
        return GetTextureInternal(id, vecPaths);
    }

    template <typename... stringVT>
    static void *AddTexture(SDL_Renderer &renderer, std::string &id, stringVT... paths)
    {
        std::vector<std::string> vecPaths = {paths...};
        TextureManager::AddTextureInternal(renderer, id, vecPaths);
    }


    // Load Textures
    static void TextureLazyLoad(SDL_Renderer &renderer);

    // UNload Textures
    static void TextureProcessUnload();

    // Initialize a minimal placeholder texture
    static void InitPlaceholder(SDL_Renderer &renderer);
      // Clear all textures
    static void ClearAll();
private:
    // AddTextureInternal a texture
    static void AddTextureInternal(SDL_Renderer &renderer,  std::string &id, std::vector<std::string> &paths);

    static SDL_Texture *GetTextureInternal(const std::string &id,  std::vector<std::string> &paths);

    // GetTextureInternal the size of a texture
    static std::pair<int, int> GetSize(std::string &id);

    // DeleteTexture a texture
    static void DeleteTexture(std::string &id);

    static SDL_Texture* EmptyTexture(SDL_Renderer &renderer);
   

    static std::unordered_map<std::string, Texture *> textures;
    static std::queue<std::pair<std::string, std::vector<std::string>>> textureLoadingQueue;
    static std::unordered_set<std::string> queueSet;
};
