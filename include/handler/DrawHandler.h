#pragma once
#include <string>
#include <SDL3_image/SDL_image.h>

class DrawHandler
{
private:
    /* data */
public:
    DrawHandler() = delete;
    ~DrawHandler() = delete;

    static void DrawSprite(SDL_Renderer &renderer,std::string id, float &x, float &y);

    static void DrawSpriteExt(SDL_Renderer &renderer, std::string id, float &x, float &y, float &xscale, float &yscale, float rot, float alpha);
};
