#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "BasicGui.h"
#include <SDL3_image/SDL_image.h>

class GuiHandler {
public:
  
    GuiHandler() = delete;
    ~GuiHandler() = delete;

    static std::unordered_map<std::string, BasicGui*> gameInstances;

    static void AllUpdates(double& ndt);
    static void AllDraws(SDL_Renderer &renderer);              

    static void AddInstance(BasicGui* instance);
    static void Remove(BasicGui* instance);

    static void RemoveAll();
    

private:
    static std::string CreateUuid();
};
