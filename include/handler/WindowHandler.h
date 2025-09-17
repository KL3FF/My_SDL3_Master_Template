#pragma once
#include <SDL3/SDL.h>
#include "ConfigManager.h"

class WindowHandler
{
public:
    WindowHandler();
    ~WindowHandler();

    SDL_Window *GetWindow() const { return window; }
    SDL_Renderer *GetRenderer() const { return renderer; }

    void HandleEvent(const SDL_Event &event);
    void LimitFPS();
    void Render();

    bool IsRunning() const { return isRunning; }
    bool IsVSYNC() const { return vsyncEnabled; }
    bool IsFS() const { return fullscreenEnabled; }

    double& DeltaTime() { return deltaTime; }
    void UpdateTime();
    void ShowDeltaTime();

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    Uint64 lastCounter;
    double deltaTime = 0.0;

    int screenWidth = 1280;
    int screenheight = 720;
    const char *title =  "SDL3 Master Template";
    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;
    bool vsyncEnabled = false;
    bool fullscreenEnabled = false;
    int fpsOptions[5] = {30, 60, 120, 144, 0};
    int fpsIndex = 1;
    double targetFPS = fpsOptions[fpsIndex];
    double targetFrameTime = 1000.0 / targetFPS;

    bool isRunning = true;

    Uint64 frameStart;

};