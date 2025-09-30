#pragma once
#include <string>
#include <iostream>

// ===================== BasicObject =====================
class BasicObject {
public:
    std::string uuid;
    float x = 0.0f;
    float y = 0.0f;
    float depth = 0.0f;
    float angle = 0.0f;

    BasicObject(float startX, float startY);
    virtual ~BasicObject();
    virtual void Draw();
    virtual void Update(double& ndt);
};

// ===================== Player =====================
class Player : public BasicObject {
public:
    Player(float startX, float startY);
    ~Player();
    void Update(double& ndt);

    void Draw();
};
