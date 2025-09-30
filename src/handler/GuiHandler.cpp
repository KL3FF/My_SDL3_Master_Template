#include "GuiHandler.h"
#include "BasicGui.h"
#include <random>
#include <SDL3_image/SDL_image.h>

std::unordered_map<std::string, BasicGui*> GuiHandler::gameInstances;

void GuiHandler::AllUpdate(double& ndt) 
{
    // loop for all instance
    for (auto& [uuid, instance] : gameInstances) {
        if (instance) {
            instance->Update(ndt);
        }
    }
}

void GuiHandler::AllDraw(SDL_Renderer &renderer) 
{
    for (auto& [uuid, instance] : gameInstances) {
        if (instance) {
            instance->Draw();
        }
    }
}


void GuiHandler::AddInstance(BasicGui* instance) 
{
    std::string uuid = CreateUuid();

   
    while (gameInstances.find(uuid) != gameInstances.end()) {
        uuid = CreateUuid();
    }

    instance->uuid = uuid;
    gameInstances[uuid] = instance;
}

void GuiHandler::Remove(BasicGui* instance) 
{
    auto it = gameInstances.find(instance->uuid);
    if (it != gameInstances.end()) {
        gameInstances.erase(it);
        delete instance;
    }
    
}

void GuiHandler::RemoveAll() 
{
    for (auto& pair : gameInstances) {
        delete pair.second;
    }
    gameInstances.clear();
}


std::string GuiHandler::CreateUuid() {
    static std::mt19937 gen{ std::random_device{}() };
    static std::uniform_int_distribution<> dis(0, 15);
    std::string uuid;
    uuid.reserve(32);

    for (int i = 0; i < 32; ++i) {
        int val = dis(gen);
        if (val < 10) uuid += ('0' + val);
        else uuid += ('a' + (val - 10));
    }
    return uuid;
}