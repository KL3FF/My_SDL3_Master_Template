#pragma once
#include <filesystem>
#include <string>
#include "ConfigInfo.h"
#include <nlohmann/json.hpp>

class ConfigManager {
public:

    static void load();

    static void save();

    template<typename T>
    static T get(const std::string& key, const T& defaultValue);

    template<typename T>
    static void set(const std::string& key, const T& value);

private:
    static nlohmann::json j;
    static std::filesystem::path path;


    static std::filesystem::path getConfigPath();

};

template<typename T>
T ConfigManager::get(const std::string& key, const T& defaultValue) {
    if (!j.contains(key)) {
        j[key] = defaultValue;
    }
    return j.value(key, defaultValue);
}

template<typename T>
void ConfigManager::set(const std::string& key, const T& value) {
    j[key] = value;
}
