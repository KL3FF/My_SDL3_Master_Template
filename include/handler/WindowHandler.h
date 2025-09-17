#pragma once
#include <SDL3/SDL.h>

class WindowHandler
{
public:
    WindowHandler(const char *title, int w, int h, SDL_WindowFlags flags);
    ~WindowHandler();

    SDL_Window *GetWindow() const { return window; }
    SDL_Renderer *GetRenderer() const { return renderer; }

    void HandleEvent(const SDL_Event &event);
    void LimitFPS();
    void Render();

    bool IsRunning() const { return isRunning; }
    bool IsVSYNC() const { return vsyncEnabled; }

    double& DeltaTime() { return deltaTime; }
    void UpdateTime();
    void ShowDeltaTime();

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    Uint64 lastCounter;
    double deltaTime = 0.0;

    bool vsyncEnabled = false;
    int fpsOptions[5] = {30, 60, 120, 144, 0};
    int fpsIndex = 1;
    double targetFPS = fpsOptions[fpsIndex];
    double targetFrameTime = 1000.0 / targetFPS;

    bool isRunning = true;

    Uint64 frameStart;

};