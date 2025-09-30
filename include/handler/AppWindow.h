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
    void SetRunning(bool _isRunning);
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

    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;
    bool isRunning = true;
};