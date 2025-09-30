#include <iostream>
#include "BasicObject.h"
#include "TextureHandler.h"
#include <SDL3_image/SDL_image.h>
#include "TextureHandler.h"
// ===================== BasicObject =====================

// Konstruktor
BasicObject::BasicObject(float _x, float _y, float _depth) : x(_x), y(_y), depth(_depth)
{
     std::cout << "BasicObject Draw at (" << x << ", " << y << ", " << depth << ")\n";
    // optional: Initialisierung
}

// Destruktor
BasicObject::~BasicObject()
{
    std::cout << "BasicObject destroyed: " << uuid << "\n";
}

// Draw-Funktion
void BasicObject::Draw(SDL_Renderer &renderer)
{
    std::cout << "BasicObject Draw at (" << x << ", " << y << ", " << depth << ")\n";
}

// Update-Funktion
void BasicObject::Update(double &ndt)
{
    std::cout << "BasicObject Update at (" << x << ", " << y << ", " << depth << ")\n";
}

// ===================== Player =====================

// Konstruktor
Player::Player(float _x, float _y, float _depth) : BasicObject(_x, _y, _depth)
{
}
Player::~Player()
{
    std::cout << "Player destroyed\n";
}

// Update-Funktion
void Player::Update(double &ndt)
{
    x +=  1.5 * ndt;
    std::cout << "BasicObject Draw at (" << x << ", " << y << ", " << depth << ")\n";
    if (x > 1640)
    {
        x = -100;
    }
   std::cout << "BasicObject Draw at (" << x << ", " << y << ", " << depth << ")\n";
}

// Draw-Funktion
void Player::Draw(SDL_Renderer &renderer)
{

        SDL_FRect src2 = {0, 0, 128, 128};
        SDL_FRect dst2 = {x, y, 128, 128};
        SDL_RenderTexture(&renderer, TextureManager::GetTexture("test2", "assets/sprites/high/hero/test2.png"), &src2, &dst2);

    // std::cout << "Drawing Player at (" << x << ", " << y << ")\n";
}



