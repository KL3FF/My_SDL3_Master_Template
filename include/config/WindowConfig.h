#pragma once


#include "ConfigHandler.h"

namespace WindowConfig
{

    // 🖥️ Bildschirm & Render Settings
    inline int screenWidth = 1280;
    inline int screenHeight = 720;
    inline bool vsyncEnabled = false;
    inline bool fullscreenEnabled = false;
    inline int textureQuality = 0;

    // ⏱️ Zeitsteuerung
    inline double deltaTime = 0.0;
    inline double targetFPS = 60.0;
    inline int fpsOptions[5] = {30, 60, 120, 144, 0};
    inline int fpsIndex = 1;

    // 🔁 Bildschirmgröße manuell aktualisieren
    inline void updateScreenSize(int w, int h)
    {
        screenWidth = w;
        screenHeight = h;
    }

    // 📏 Bildschirmgröße abrufen
    inline int getScreenWidth() { return screenWidth; }
    inline void setScreenWidth(int w) { screenWidth = w; }

    inline int getScreenHeight() { return screenHeight; }
    inline void setScreenHeight(int h) { screenHeight = h; }
    // 🖥️ VSync setzen / holen
    inline void setVSync(bool enabled) { vsyncEnabled = enabled; }
    inline bool isVSyncEnabled() { return vsyncEnabled; }

    // 🖥️ Vollbild setzen / holen
    inline void setFullscreen(bool enabled) { fullscreenEnabled = enabled; }
    inline bool isFullscreen() { return fullscreenEnabled; }

    // 🖼️ Texture Quality setzen / holen
    inline void setTextureQuality(int quality) { textureQuality = quality; }
    inline int getTextureQuality() { return textureQuality; }

    // 🎯 FPS Index & Optionen
    inline void setFpsIndex(int index)
    {
        if (index >= 0 && index < 5)
            fpsIndex = index;
    }
    inline int getFpsIndex() { return fpsIndex; }

    inline int getTargetFps() { return fpsOptions[fpsIndex]; }

    inline void OpenConfig()
    {
        ConfigHandler::OpenConfig();
        fullscreenEnabled = ConfigHandler::GetConfigValue("fullscreen", false);
        vsyncEnabled = ConfigHandler::GetConfigValue("vsync", false);
        screenWidth = ConfigHandler::GetConfigValue("width", 1280);
        screenHeight = ConfigHandler::GetConfigValue("height", 720);
        textureQuality = ConfigHandler::GetConfigValue("textureQuality", 0);
        ConfigHandler::SaveConfig();
    }

    inline void SaveConfig()
    {
        ConfigHandler::OpenConfig();
        ConfigHandler::SetConfigValue("fullscreen", fullscreenEnabled);
        ConfigHandler::SetConfigValue("vsync", vsyncEnabled);
        ConfigHandler::SetConfigValue("width", screenWidth);
        ConfigHandler::SetConfigValue("height", screenHeight);
        ConfigHandler::SetConfigValue("textureQuality", textureQuality);
        ConfigHandler::SaveConfig();
    }

}
