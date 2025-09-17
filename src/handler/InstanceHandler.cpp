#include "InstanceHandler.h"


std::unordered_map<std::string, BaseObject*> InstanceHandler::gameInstances;

void InstanceHandler::AllUpdate(double& ndt) 
{
   
}

void InstanceHandler::AllDraw() 
{
   
}

// InstanceHandler::Add(new Player());
void InstanceHandler::Add(BaseObject* instance) 
{
    std::string uuid = CreateUuid();

   
    while (gameInstances.find(uuid) != gameInstances.end()) {
        uuid = CreateUuid();
    }

    instance->uuid = uuid;
    gameInstances[uuid] = instance;
}

void InstanceHandler::Remove(BaseObject* instance) 
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
  
    ///
}
