#include "InstanceHandler.h"
#include "BasicObject.h"


std::unordered_map<std::string, BasicObject*> InstanceHandler::gameInstances;

void InstanceHandler::AllUpdate(double& ndt) 
{
    // Schleife über alle gespeicherten Instanzen
    for (auto& [uuid, instance] : gameInstances) {
        if (instance) {
            instance->Update(ndt);
        }
    }
}

void InstanceHandler::AllDraw() 
{
    for (auto& [uuid, instance] : gameInstances) {
        if (instance) {
            instance->Draw();
        }
    }
}

// InstanceHandler::AddInstance(new Player());
void InstanceHandler::AddInstance(BasicObject* instance) 
{
    std::string uuid = CreateUuid();

   
    while (gameInstances.find(uuid) != gameInstances.end()) {
        uuid = CreateUuid();
    }

    instance->uuid = uuid;
    gameInstances[uuid] = instance;
}

void InstanceHandler::Remove(BasicObject* instance) 
{
    auto it = gameInstances.find(instance->uuid);
    if (it != gameInstances.end()) {
        gameInstances.erase(it);
        delete instance;
    }
    
}

void InstanceHandler::RemoveAll() 
{
    for (auto& pair : gameInstances) {
        delete pair.second;
    }
    gameInstances.clear();
}


std::string InstanceHandler::CreateUuid() 
{

}
