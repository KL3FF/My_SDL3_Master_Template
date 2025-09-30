#pragma once
#include <string>
#include <iostream>
#include <SDL3_image/SDL_image.h>

// ===================== BasicObject =====================
class BasicObject
{
public:
    std::string uuid;
    float x = 0.0f;
    float y = 0.0f;
    float depth = 0.0f;
    float angle = 0.0f;

    BasicObject(SDL_Renderer &renderer, float _x, float _y, float _depth);
    virtual ~BasicObject();
    virtual void Update(SDL_Renderer &renderer, double &ndt);
    virtual void Draw(SDL_Renderer &renderer);

};

// ===================== Player =====================
class Player : public BasicObject
{
public:
    Player(SDL_Renderer &renderer, float _x, float _y, float _depth);
    ~Player();
    void Update(SDL_Renderer &renderer, double &ndt);

    void Draw(SDL_Renderer &renderer);
};



    