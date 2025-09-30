#pragma once
#include <string>
#include <iostream>

// ===================== BasicGui =====================
class BasicGui
{
public:
    std::string uuid;
    float x = 0.0f;
    float y = 0.0f;
    float depth = 0.0f;
    float angle = 0.0f;

    BasicGui(float _x, float _y, float _depth);
    virtual ~BasicGui();
    virtual void Draw();
    virtual void Update(double &ndt);
};

// ===================== StartGui =====================
class StartGui : public BasicGui
{
public:
    StartGui(float _x, float _y, float _depth);
    ~StartGui();
    void Update(double &ndt);

    void Draw();
};
