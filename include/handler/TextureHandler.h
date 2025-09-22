#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>
#include <iostream>

// Helper structure for textures
struct Texture
{
    SDL_Texture* tex;
    float ttl = 300; // Time to live in seconds
    int width;
    int height;
    

    Texture(SDL_Texture* t, int w, int h);
    ~Texture();
};

class TextureManager
{
public:
    // Add a texture
    static void Add(SDL_Renderer& renderer, const std::string& id, const std::string& filename);

    // Get a texture
    static SDL_Texture* Get(const std::string& id);

    // Get the size of a texture
    static std::pair<int,int> GetSize(const std::string& id);

    // Delete a texture
    static void Delete(const std::string& id);

    // Clear all textures
    static void ClearAll();

private:
    static std::unordered_map<std::string, Texture*> textures;
};
