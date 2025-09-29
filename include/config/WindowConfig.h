#pragma once

#include "ConfigHandler.h"

namespace WindowConfig
{

    // Screen & render settings
    inline int screenWidth = 1280;
    inline int screenHeight = 720;
    inline bool vsyncEnabled = false;
    inline bool fullscreenEnabled = false;
    inline int textureQuality = 0;

    // Timing control
    inline double deltaTime = 0.0;
    inline double targetFPS = 60.0;
    inline int fpsOptions[5] = {30, 60, 120, 144, 0};
    inline int fpsIndex = 1;

    // Manually update screen size
    inline void updateScreenSize(int w, int h)
    {
        screenWidth = w;
        screenHeight = h;
    }

    // Get screen width
    inline int getScreenWidth() { return screenWidth; }
    inline void setScreenWidth(int w) { screenWidth = w; }

    // Get screen height
    inline int getScreenHeight() { return screenHeight; }
    inline void setScreenHeight(int h) { screenHeight = h; }

    // Set/get VSync
    inline void setVSync(bool enabled) { vsyncEnabled = enabled; }
    inline bool isVSyncEnabled() { return vsyncEnabled; }

    // Set/get fullscreen
    inline void setFullscreen(bool enabled) { fullscreenEnabled = enabled; }
    inline bool isFullscreen() { return fullscreenEnabled; }

    // Set/get texture quality
    inline void setTextureQuality(int quality) { textureQuality = quality; }
    inline int getTextureQuality() { return textureQuality; }

    // FPS index & options
    inline void setFpsIndex(int index)
    {
        if (index >= 0 && index < 5)
            fpsIndex = index;
    }
    inline int getFpsIndex() { return fpsIndex; }

    inline int getTargetFps() { return fpsOptions[fpsIndex]; }

    // Load configuration from file
    inline void LoadConfig()
    {
        ConfigHandler::OpenConfig();

        fullscreenEnabled = ConfigHandler::GetBool("fullscreen", false);
        vsyncEnabled      = ConfigHandler::GetBool("vsync", false);
        screenWidth       = ConfigHandler::GetInt("width", 1280);
        screenHeight      = ConfigHandler::GetInt("height", 720);
        textureQuality    = ConfigHandler::GetInt("textureQuality", 0);

        ConfigHandler::SaveConfig(); 
    }

    // Save configuration to file
    inline void SaveConfig()
    {
        ConfigHandler::OpenConfig(); // reload file

        ConfigHandler::SetValue("fullscreen", fullscreenEnabled);
        ConfigHandler::SetValue("vsync", vsyncEnabled);
        ConfigHandler::SetValue("width", screenWidth);
        ConfigHandler::SetValue("height", screenHeight);
        ConfigHandler::SetValue("textureQuality", textureQuality);

        ConfigHandler::SaveConfig();
    }

}
