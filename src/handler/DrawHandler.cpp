#include "DrawHandler.h"
#include <string>
#include <SDL3_image/SDL_image.h>
#include "TextureHandler.h"

void DrawHandler::DrawSprite(SDL_Renderer &renderer, std::string id, float &x, float &y)
{
        SDL_FRect src2 = {0, 0, 128, 128};
        SDL_FRect dst2 = {x, y, 128, 128};
        SDL_RenderTexture(&renderer, TextureManager::GetTexture(id), &src2, &dst2);

}

void DrawSpriteExt(SDL_Renderer &renderer, std::string &id, float &x, float &y, float &xscale, float &yscale, float rot, float alpha)
{

}