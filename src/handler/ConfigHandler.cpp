#include "AppInfo.h"
#include "ConfigHandler.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdlib>

std::unordered_map<std::string, std::string> ConfigHandler::data;

//  Load configuration file
void ConfigHandler::OpenConfig() {
    // Automatically determine config path
    std::filesystem::path path = GetConfigPath();

    // Ensure directory exists
    std::filesystem::create_directories(path.parent_path());

    // Open file
    std::ifstream file(path);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        size_t pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        // Remove whitespace
        key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
        value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

        data[key] = value;
    }
}


//  Save configuration file
void ConfigHandler::SaveConfig() {
    // Automatically determine config path
    std::filesystem::path path = GetConfigPath();

    // Overwrite file completely
    std::ofstream file(path);
    for (auto& [key, value] : data) {
        file << key << " = " << value << "\n";
    }

    // Clear memory after saving
    data.clear();
}


//  Getter functions
bool ConfigHandler::GetBool(const std::string& key, bool defaultValue) {
    if (data.find(key) == data.end()) {
        data[key] = defaultValue ? "true" : "false";
        return defaultValue;
    }
    std::string val = data[key];
    std::transform(val.begin(), val.end(), val.begin(), ::tolower);
    if (val == "true" || val == "1") return true;
    if (val == "false" || val == "0") return false;
    data[key] = defaultValue ? "true" : "false";
    return defaultValue;
}

int ConfigHandler::GetInt(const std::string& key, int defaultValue) {
    if (data.find(key) == data.end()) {
        data[key] = std::to_string(defaultValue);
        return defaultValue;
    }
    try {
        return std::stoi(data[key]);
    } catch (...) {
        data[key] = std::to_string(defaultValue);
        return defaultValue;
    }
}

float ConfigHandler::GetFloat(const std::string& key, float defaultValue) {
    if (data.find(key) == data.end()) {
        std::ostringstream oss;
        oss << defaultValue;
        data[key] = oss.str();
        return defaultValue;
    }
    try {
        return std::stof(data[key]);
    } catch (...) {
        std::ostringstream oss;
        oss << defaultValue;
        data[key] = oss.str();
        return defaultValue;
    }
}

std::string ConfigHandler::GetString(const std::string& key, const std::string& defaultValue) {
    if (data.find(key) == data.end()) {
        data[key] = defaultValue;
        return defaultValue;
    }
    return data[key];
}

//  Setter functions
void ConfigHandler::SetValue(const std::string& key, bool value) {
    data[key] = value ? "true" : "false";
}

void ConfigHandler::SetValue(const std::string& key, int value) {
    data[key] = std::to_string(value);
}

void ConfigHandler::SetValue(const std::string& key, float value) {
    std::ostringstream oss;
    oss << value;
    data[key] = oss.str();
}

void ConfigHandler::SetValue(const std::string& key, const std::string& value) {
    data[key] = value;
}

//  Automatically determine config file path
std::filesystem::path ConfigHandler::GetConfigPath() {
#ifdef _WIN32
    const char* appdata = std::getenv("APPDATA");
    std::filesystem::path base = appdata ? std::filesystem::path(appdata) / PROJECT_NAME
                                         : std::filesystem::current_path();
#elif __linux__
    const char* xdg = std::getenv("XDG_CONFIG_HOME");
    std::filesystem::path base;
    if (xdg) {
        base = std::filesystem::path(xdg) / "PROJECT_NAME";
    } else {
        const char* home = std::getenv("HOME");
        base = home ? std::filesystem::path(home) / ".config" / PROJECT_NAME
                    : std::filesystem::current_path() / PROJECT_NAME;
    }
#else
    std::cerr << "Unsupported platform! Exiting.\n";
    std::exit(EXIT_FAILURE);
#endif

    std::filesystem::create_directories(base);
    return base / "config.cfg";
}
