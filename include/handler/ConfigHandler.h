#pragma once
#include <string>
#include <unordered_map>
#include <filesystem>

class ConfigHandler {
public:
    ConfigHandler() = delete;
    ~ConfigHandler() = delete;
    // data load
    static void OpenConfig();

    // data save
    static void SaveConfig();

    // type getter
    static bool GetBool(const std::string& key, bool defaultValue);
    static int GetInt(const std::string& key, int defaultValue);
    static float GetFloat(const std::string& key, float defaultValue);
    static std::string GetString(const std::string& key, const std::string& defaultValue);

    // type setter
    static void SetValue(const std::string& key, bool value);
    static void SetValue(const std::string& key, int value);
    static void SetValue(const std::string& key, float value);
    static void SetValue(const std::string& key, const std::string& value);

    // get save path
    static std::filesystem::path GetConfigPath();

private:
    static std::unordered_map<std::string, std::string> data;
};
