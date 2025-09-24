#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

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
    static bool LoadBundle();
    static bool RemoveFile(const std::string &path);
    static void ClearAllFiles();
    static void PrintAllEntries();
    static std::vector<uint8_t> GetFileData(const std::string& fullPathInBundle);
private:
    static std::unordered_map<std::string, BundleEntry *> bundleEntries;
};
