#pragma once
#include <filesystem>
#include <string>
#include <nlohmann/json.hpp>

class ConfigHandler {
public:

    static void OpenConfig();
 
    static void SaveConfig();

    template<typename T>
    static T GetConfigValue(const std::string& key, const T& defaultValue);

    template<typename T>
    static void SetConfigValue(const std::string& key, const T& value);

private:
    static nlohmann::json j;
    static std::filesystem::path path;

    static std::filesystem::path GetConfigPath();

};

template<typename T>
T ConfigHandler::GetConfigValue(const std::string& key, const T& defaultValue) {
    if (!j.contains(key)) {
        j[key] = defaultValue;
    }
    return j.value(key, defaultValue);
}

template<typename T>
void ConfigHandler::SetConfigValue(const std::string& key, const T& value) {
    j[key] = value;
}
