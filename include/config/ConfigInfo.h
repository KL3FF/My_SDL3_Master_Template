#pragma once

#define PROJECT_NAME "My Test App"
#define PROJECT_VERSION_MAJOR "1"
#define PROJECT_VERSION_MINOR "0"
#define PROJECT_VERSION_PATCH "0"



#pragma once
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif


inline std::filesystem::path exeDir;

inline void initExeDir() {
#ifdef _WIN32
    char path[MAX_PATH];
    GetModuleFileNameA(nullptr, path, MAX_PATH);
    exeDir = std::filesystem::path(path).parent_path();
#else
    char buf[4096];
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (len != -1) {
        buf[len] = '\0';
        exeDir = std::filesystem::path(buf).parent_path();
    } else {
        exeDir = std::filesystem::current_path();
    }
#endif
}
