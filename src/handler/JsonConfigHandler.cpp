#include <fstream>
#include <iostream>
#include "JsonConfigHandler.h"
#include "ConfigInfo.h"

nlohmann::json JsonConfigHandler::j;
std::filesystem::path JsonConfigHandler::path;

void JsonConfigHandler::Load() {
    path = GetConfigPath();

    std::filesystem::create_directories(path.parent_path());

    std::ifstream file(path);
    if (file.is_open()) {
        file >> j;
    }
}

void JsonConfigHandler::Save() {
    std::ofstream(path) << j.dump(4); 
}

std::filesystem::path JsonConfigHandler::GetConfigPath() {
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

    return base / "config.json";
}
