#pragma once
#include <filesystem>
#include <string>
#include <nlohmann/json.hpp>

class JsonConfigHandler {
public:

    static void Load();
 
    static void Save();

    template<typename T>
    static T Get(const std::string& key, const T& defaultValue);

    template<typename T>
    static void Set(const std::string& key, const T& value);

private:
    static nlohmann::json j;
    static std::filesystem::path path;


    static std::filesystem::path GetConfigPath();

};

template<typename T>
T JsonConfigHandler::Get(const std::string& key, const T& defaultValue) {
    if (!j.contains(key)) {
        j[key] = defaultValue;
    }
    return j.value(key, defaultValue);
}

template<typename T>
void JsonConfigHandler::Set(const std::string& key, const T& value) {
    j[key] = value;
}
