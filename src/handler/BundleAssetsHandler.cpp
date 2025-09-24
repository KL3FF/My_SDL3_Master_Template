#include "BundleAssetsHandler.h"
#include "ConfigInfo.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

std::unordered_map<std::string, BundleEntry *> BundleAssetsHandler::bundleEntries;

bool BundleAssetsHandler::LoadBundle()
{
    ClearAllFiles(); // delete previous entries

    for (const auto &entry : std::filesystem::recursive_directory_iterator(exeDir))
    {
        if (!entry.is_regular_file())
            continue;

        std::filesystem::path path = entry.path();

        if (path.extension() != ".pak")
            continue;

        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open PAK: " << path << "\n";
            continue;
        }

        // --- Check signature ---
        char signature[4];
        file.read(signature, 4);
        if (std::string(signature, 4) != "PACK")
        {
            std::cerr << "Error: Invalid PAK file: " << path << "\n";
            continue;
        }
        // --- Read directory offset & size ---
        uint32_t directoryOffset, directorySize;
        file.read(reinterpret_cast<char *>(&directoryOffset), 4);
        file.read(reinterpret_cast<char *>(&directorySize), 4);

        // --- Jump to directory ---
        file.seekg(directoryOffset, std::ios::beg);
        uint32_t numFiles = directorySize / (200 + 4 + 4); // Path + Offset + Size

        for (uint32_t i = 0; i < numFiles; ++i)
        {
            char pathBuf[200];
            file.read(pathBuf, 200);
            std::string storedPath(pathBuf);
            storedPath = storedPath.substr(0, storedPath.find('\0')); // Remove null terminator

            uint32_t offset, size;
            file.read(reinterpret_cast<char *>(&offset), 4);
            file.read(reinterpret_cast<char *>(&size), 4);

            std::string name = std::filesystem::path(storedPath).filename().string();
            std::string extension = std::filesystem::path(storedPath).extension().string();
            std::string pakPath = std::filesystem::relative(path, exeDir).string();

            if (!extension.empty() && extension[0] == '.')
            {
                extension = extension.substr(1);
            }

            bundleEntries[storedPath] = new BundleEntry{offset, size, storedPath, pakPath, name, extension};
        }

        file.close();
    }

    return true;
}

bool BundleAssetsHandler::RemoveFile(const std::string &filePath)
{
    auto it = bundleEntries.find(filePath);
    if (it != bundleEntries.end())
    {
        delete it->second;
        bundleEntries.erase(it);
        return true;
    }
    return false;
}

void BundleAssetsHandler::ClearAllFiles()
{
    for (auto &pair : bundleEntries)
    {
        delete pair.second;
    }
    bundleEntries.clear();
}

void BundleAssetsHandler::PrintAllEntries()
{
    std::cout << "Bundle contains " << bundleEntries.size() << " entries:\n";
    for (const auto &pair : bundleEntries)
    {
        const BundleEntry *entry = pair.second;
        std::cout << "FullPath : " << entry->fullPath << "\n";
        std::cout << "PakPath  : " << entry->pakPath << "\n";
        std::cout << "Name     : " << entry->name << "\n";
        std::cout << "Extension: " << entry->extension << "\n";
        std::cout << "Offset   : " << entry->offset << "\n";
        std::cout << "Size     : " << entry->size << "\n";
        std::cout << "---------------------------\n";
    }
}

std::vector<uint8_t> BundleAssetsHandler::GetFileData(const std::string &fullPathInBundle)
{
    auto it = BundleAssetsHandler::bundleEntries.find(fullPathInBundle);
    if (it == BundleAssetsHandler::bundleEntries.end())
    {
        return {};
    }

    BundleEntry *entry = it->second;

    std::filesystem::path fullPakPath = std::filesystem::path(exeDir) / entry->pakPath;
    std::ifstream pakFile(fullPakPath, std::ios::binary);

    if (!pakFile.is_open()){
        return {};
    }
  
    pakFile.seekg(entry->offset, std::ios::beg);

    std::vector<uint8_t> data(entry->size);
    pakFile.read(reinterpret_cast<char *>(data.data()), entry->size);

    return data;
}