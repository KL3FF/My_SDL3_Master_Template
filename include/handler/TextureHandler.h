#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>
#include <iostream>

// Hilfsstruktur für Texturen
struct Texture
{
    SDL_Texture* tex;
    int width;
    int height;

    Texture(SDL_Texture* t, int w, int h);
    ~Texture();
};

class TextureManager
{
public:
    // Textur hinzufügen
    static void Add(SDL_Renderer& renderer, const std::string& id, const std::string& filename);

    // Textur holen
    static SDL_Texture* Get(const std::string& id);

    // Größe holen
    static std::pair<int,int> GetSize(const std::string& id);

    // Textur löschen
    static void Delete(const std::string& id);

    // Alle Texturen löschen
    static void ClearAll();

private:
    static std::unordered_map<std::string, Texture*> textures;
};
