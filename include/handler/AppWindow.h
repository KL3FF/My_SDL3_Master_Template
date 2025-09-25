#pragma once
#include <SDL3/SDL.h>


class AppWindow
{
public:
    AppWindow();
    ~AppWindow();

    SDL_Window &GetWindow() const { return *window; }
    SDL_Renderer &GetRenderer() const { return *renderer; }

    void HandleEvent(const SDL_Event &event);
    void LimitFPS();
    void Render();

    bool IsRunning() const { return isRunning; }
    bool IsVSYNC() const { return vsyncEnabled; }
    bool IsFS() const { return fullscreenEnabled; }

    int &TextureQuality() { return textureQuality; }
    double &DeltaTime() { return deltaTime; }
    void UpdateTime();
    void ShowDeltaTime();

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    const char *title = "SDL3 Master Template";

    Uint64 lastCounter;
    Uint64 frameStart;

    double deltaTime = 0.0;
    double targetFPS = 60.0;
    double targetFrameTime = 16.6667;

    int screenWidth = 1280;
    int screenHeight = 720;
    int textureQuality = 0;
    int fpsOptions[5] = {30, 60, 120, 144, 0};
    int fpsIndex = 1;

    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;

    bool vsyncEnabled = false;
    bool fullscreenEnabled = false;
    bool isRunning = true;
};