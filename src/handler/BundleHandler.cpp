#include "BundleHandler.h"
#include "ConfigInfo.h"

#include <filesystem>
#include <iostream>


std::unordered_map<std::string, BundleEntry*> BundleHandler::bundleEntries;

bool BundleHandler::loadBundle(const std::string& relativePath) {

    std::filesystem::path bundlePath = exeDir / relativePath;
    std::ifstream file(bundlePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Fehler: Bundle konnte nicht geladen werden! Pfad: " << bundlePath << "\n";
        return false;
    }

    uint32_t numFiles;
    file.read(reinterpret_cast<char*>(&numFiles), sizeof(uint32_t));

    for (uint32_t i = 0; i < numFiles; ++i) {
        char pathBuf[200];
        file.read(pathBuf, 200);
        std::string fullPath(pathBuf);
        fullPath = fullPath.substr(0, fullPath.find('\0'));

        uint32_t offset, size;
        file.read(reinterpret_cast<char*>(&offset), 4);
        file.read(reinterpret_cast<char*>(&size), 4);

        std::string name = fullPath.substr(fullPath.find_last_of("/\\") + 1);
        std::string extension;
        size_t dotPos = name.find_last_of('.');
        if (dotPos != std::string::npos) {
            extension = name.substr(dotPos);
        }

        BundleEntry* entry = new BundleEntry{offset, size, fullPath, name, extension};
        bundleEntries[fullPath] = entry;
    }

    return true;
}

bool BundleHandler::removeFile(const std::string& filePath) {
    auto it = bundleEntries.find(filePath);
    if (it != bundleEntries.end()) {
        delete it->second;
        bundleEntries.erase(it);
        return true;
    }
    return false;
}

void BundleHandler::clearAllFiles() {
    for (auto& pair : bundleEntries) {
        delete pair.second;
    }
    bundleEntries.clear();
}

void BundleHandler::printAllEntries() {
    std::cout << "Bundle enthält " << bundleEntries.size() << " Einträge:\n";
    for (const auto& pair : bundleEntries) {
        const BundleEntry* entry = pair.second;
        std::cout << "FullPath : " << entry->fullPath << "\n";
        std::cout << "Name     : " << entry->name << "\n";
        std::cout << "Extension: " << entry->extension << "\n";
        std::cout << "Offset   : " << entry->offset << "\n";
        std::cout << "Size     : " << entry->size << "\n";
        std::cout << "---------------------------\n";
    }
}