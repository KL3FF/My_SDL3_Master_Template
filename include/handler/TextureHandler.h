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
    SDL_Texture *tex; // Pointer to SDL texture
    int ttl = 300;    // Time to live (number of cycles before unloading)
    int width;        // Texture width
    int height;       // Texture height
    bool persistent;  // If true, texture is never automatically unloaded

    // Constructor
    Texture(SDL_Texture *_tex, int _width, int _height, int _ttl, bool _persistent);
    // Destructor frees SDL texture
    ~Texture();

    // Getter and setter functions
    int GetTTL();
    void SetTTL(int _ttl);
    bool GetPersistent();
    void SetPersistent(bool _persistent);
};

class TextureManager
{
public:
    // Get a texture by ID, add paths for lazy loading if not loaded yet
    template <typename... stringVT>
    static SDL_Texture *GetTexture(const std::string &id, stringVT... paths)
    {
        std::vector<std::string> vecPaths = {paths...};
        if (vecPaths.empty())
        {
            // Return placeholder
            auto placeholder = textures.find("__placeholder__");
            if (placeholder != textures.end())
            {
                return placeholder->second->tex;
            }
            return nullptr;
        }
        return GetTextureInternal(id, vecPaths);
    }
    // Add a texture lazy if it doesn't exist
    template <typename... stringVT>
    static void AddTexture(const std::string &id, stringVT... paths)
    {
        std::vector<std::string> vecPaths = {paths...};
        if (vecPaths.empty())
        {
            return;
        }
        AddLazyTextureInternal(id, vecPaths);
    }

    // Add a texture immediately if it doesn't exist
    template <typename... stringVT>
    static void AddTextureInstantly(SDL_Renderer &renderer, std::string &id, stringVT... paths)
    {
        std::vector<std::string> vecPaths = {paths...};
        if (vecPaths.empty())
        {
            return;
        }

        AddTextureInternal(renderer, id, vecPaths);
    }

    // Load the next texture in the lazy loading queue
    static void TextureLazyLoad(SDL_Renderer &renderer);

    // Process unloading of textures whose TTL has expired
    static void TextureProcessUnload();

    // Initialize a minimal placeholder texture
    static void InitPlaceholder(SDL_Renderer &renderer);
    // Clear all textures
    static void ClearAll();

private:
    static const int maxTTL = 300; // Maximum TTL for textures

    // Internal function to add a texture
    static void AddTextureInternal(SDL_Renderer &renderer, std::string &id, std::vector<std::string> &paths);

    static void AddLazyTextureInternal(const std::string &id, std::vector<std::string> &paths);

    // Internal function to get a texture by ID
    static SDL_Texture *GetTextureInternal(const std::string &id, std::vector<std::string> &paths);

    // Get the size of a texture
    static std::pair<int, int> GetSize(std::string &id);

    // Delete a texture manually
    static void DeleteTexture(std::string &id);

    // Create a minimal empty texture as fallback
    static SDL_Texture *EmptyTexture(SDL_Renderer &renderer);

    // Map of loaded textures
    static std::unordered_map<std::string, Texture *> textures;
    // Iterator used for TTL-based unloading
    static std::unordered_map<std::string, Texture *>::iterator currentIt;

    // Queue for lazy loading textures
    static std::queue<std::pair<std::string, std::vector<std::string>>> textureLoadingQueue;
    // Set to prevent duplicate entries in the queue
    static std::unordered_set<std::string> queueSet;
};