

#pragma once
#include <string>

class Mask2D;

class BaseObject {
public:
    std::string uuid;
    float x = 0.0f;
    float y = 0.0f;
    float depth = 0.0f;
    float angle = 0.0f;

    BaseObject();

    ~BaseObject();


    void Draw();
    void Update(double& ndt);
};
