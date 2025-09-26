#pragma once
#include <filesystem>
#include <string>
#include <nlohmann/json.hpp>

class JsonConfigHandler {
public:

    static void LoadJson();
 
    static void SaveJson();

    template<typename T>
    static T GetJsonValue(const std::string& key, const T& defaultValue);

    template<typename T>
    static void SetJsonValue(const std::string& key, const T& value);

private:
    static nlohmann::json j;
    static std::filesystem::path path;

    static std::filesystem::path GetConfigPath();

};

template<typename T>
T JsonConfigHandler::GetJsonValue(const std::string& key, const T& defaultValue) {
    if (!j.contains(key)) {
        j[key] = defaultValue;
    }
    return j.value(key, defaultValue);
}

template<typename T>
void JsonConfigHandler::SetJsonValue(const std::string& key, const T& value) {
    j[key] = value;
}
