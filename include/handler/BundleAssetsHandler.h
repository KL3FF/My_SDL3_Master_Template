#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <filesystem>

struct BundleEntry
{
    uint32_t offset;
    uint32_t size;
    std::string fullPath;
    std::string pakPath;
    std::string name;
    std::string extension;
};

class BundleAssetsHandler
{
public:
    static bool loadBundle();
    static bool removeFile(const std::string &path);
    static void clearAllFiles();
    static void printAllEntries();

private:
    static std::unordered_map<std::string, BundleEntry *> bundleEntries;
};
