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

    BasicObject(float _x, float _y, float _depth);
    virtual ~BasicObject();
    virtual void Draw(SDL_Renderer &renderer);
    virtual void Update(double &ndt);
};

// ===================== Player =====================
class Player : public BasicObject
{
public:
    Player(float _x, float _y, float _depth);
    ~Player();
    void Update(double &ndt);

    void Draw(SDL_Renderer &renderer);
};



    