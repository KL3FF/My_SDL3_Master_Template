#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "BaseObject.h"

class InstanceHandler {
public:
  
    InstanceHandler() = delete;

    static std::unordered_map<std::string, BaseObject*> gameInstances;

    static std::vector<BaseObject*> removeList;

    static void AllUpdate(double& ndt);
    static void AllDraw();              

    static void Add(BaseObject* instance);
    static void Remove(BaseObject* instance);

    static void AddToRemoveList(BaseObject* instance);
    static void RemoveAll();
    

private:
    static std::string CreateUuid();
};
