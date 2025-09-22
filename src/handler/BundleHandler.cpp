#include "BundleHandler.h"
#include "ConfigInfo.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

std::unordered_map<std::string, BundleEntry*> BundleHandler::bundleEntries;

bool BundleHandler::loadBundle(const std::string& relativePath) {
    std::filesystem::path bundlePath = exeDir / relativePath;
    std::ifstream file(bundlePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Fehler: Bundle konnte nicht geladen werden! Pfad: " << bundlePath << "\n";
        return false;
    }

    // --- 1. Signatur prüfen ---
    char signature[4];
    file.read(signature, 4);
    if (std::string(signature, 4) != "PACK") {
        std::cerr << "Fehler: Ungültige PAK-Datei!\n";
        return false;
    }

    // --- 2. Directory-Offset und -Size auslesen ---
    uint32_t directoryOffset, directorySize;
    file.read(reinterpret_cast<char*>(&directoryOffset), 4);
    file.read(reinterpret_cast<char*>(&directorySize), 4);

    // --- 3. Directory anspringen ---
    file.seekg(directoryOffset, std::ios::beg);
    uint32_t numFiles = directorySize / (200 + 4 + 4); // Pfad + Offset + Size

    for (uint32_t i = 0; i < numFiles; ++i) {
        char pathBuf[200];
        file.read(pathBuf, 200);
        std::string storedPath(pathBuf);
        storedPath = storedPath.substr(0, storedPath.find('\0')); // Null-Terminator entfernen

        uint32_t offset, size;
        file.read(reinterpret_cast<char*>(&offset), 4);
        file.read(reinterpret_cast<char*>(&size), 4);

        std::string name = std::filesystem::path(storedPath).filename().string();
        std::string extension = std::filesystem::path(storedPath).extension().string();

        BundleEntry* entry = new BundleEntry{offset, size, storedPath, name, extension};
        bundleEntries[storedPath] = entry;
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
