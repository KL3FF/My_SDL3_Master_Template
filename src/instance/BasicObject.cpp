#include <iostream>
#include "BasicObject.h"
#include "TextureHandler.h"
#include <SDL3_image/SDL_image.h>
#include "DrawHandler.h"
// ===================== BasicObject =====================

// Konstruktor
BasicObject::BasicObject(SDL_Renderer &renderer, float _x, float _y, float _depth) : x(_x), y(_y), depth(_depth)
{
    //  std::cout << "BasicObject Draw at (" << x << ", " << y << ", " << depth << ")\n";
    // optional: Initialisierung
}

// Destruktor
BasicObject::~BasicObject()
{

}
// Update-Funktion
void BasicObject::Update(SDL_Renderer &renderer, double &ndt)
{
   
}

// Draw-Funktion
void BasicObject::Draw(SDL_Renderer &renderer)
{

}


// ===================== Player =====================

// Konstruktor
Player::Player(SDL_Renderer &renderer, float _x, float _y, float _depth) : BasicObject(renderer,_x, _y, _depth)
{
    // std::cout << "Player Draw at (" << x << ", " << y << ", " << depth << ")\n";
    TextureManager::AddTextureLazy("test2", "assets/sprites/high/hero/test2.png");
}
Player::~Player()
{
    std::cout << "Player destroyed\n";
}

// Update-Funktion
void Player::Update(SDL_Renderer &renderer, double &ndt)
{
    x +=  1.5 * ndt;
    if (x > 1640)
    {
        x = -100;
    }

}

// Draw-Funktion
void Player::Draw(SDL_Renderer &renderer)
{


        DrawHandler::DrawSprite(renderer,"test2",x,y);
     
    // std::cout << "Drawing Player at (" << x << ", " << y << ")\n";
}



