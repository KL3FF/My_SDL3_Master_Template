#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "BasicObject.h"

class InstanceHandler {
public:
  
    InstanceHandler() = delete;
    ~InstanceHandler() = delete;

    static std::unordered_map<std::string, BasicObject*> gameInstances;

    static void AllUpdate(double& ndt);
    static void AllDraw();              

    static void AddInstance(BasicObject* instance);
    static void Remove(BasicObject* instance);

    static void RemoveAll();
    

private:
    static std::string CreateUuid();
};
