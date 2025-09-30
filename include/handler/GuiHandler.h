#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "BasicObject.h"
#include <SDL3_image/SDL_image.h>

class GuiHandler {
public:
  
    GuiHandler() = delete;
    ~GuiHandler() = delete;

    static std::unordered_map<std::string, BasicObject*> gameInstances;

    static void AllUpdate(double& ndt);
    static void AllDraw(SDL_Renderer &renderer);              

    static void AddInstance(BasicObject* instance);
    static void Remove(BasicObject* instance);

    static void RemoveAll();
    

private:
    static std::string CreateUuid();
};
