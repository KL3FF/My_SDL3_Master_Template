
#include <SDL3/SDL.h>
#include <iostream>
#include "WindowHandler.h"
#include "JsonConfigHandler.h"

WindowHandler::WindowHandler()
{

    JsonConfigHandler::load();
    fullscreenEnabled = JsonConfigHandler::get("fullscreen", false);
    vsyncEnabled = JsonConfigHandler::get("vsync", false);
    screenWidth  = JsonConfigHandler::get("width", 1280);
    screenHeight = JsonConfigHandler::get("height", 720);
    JsonConfigHandler::save();

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, screenWidth, screenHeight, flags);

    renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderVSync(renderer, vsyncEnabled ? 1 : 0);

    if (!fullscreenEnabled)
    {
        SDL_SetWindowFullscreen(window, 0);
    }
    else
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }

    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Fehler: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        isRunning = false;
    }
    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        isRunning = false;
    }
}

WindowHandler::~WindowHandler()
{
    JsonConfigHandler::load();
    JsonConfigHandler::set("fullscreen", fullscreenEnabled);
    JsonConfigHandler::set("vsync", vsyncEnabled);
    JsonConfigHandler::set("width", screenWidth);
    JsonConfigHandler::set("height", screenHeight);
    JsonConfigHandler::save();

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }

    if (window)
    {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();

}

void WindowHandler::HandleEvent(const SDL_Event &event)
{

    if (event.type == SDL_EVENT_QUIT)
    {
        isRunning = false;
    }

    if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
    {
        isRunning = false;
    }

    if (event.type == SDL_EVENT_WINDOW_RESIZED)
    {
        screenWidth = event.window.data1;
        screenHeight = event.window.data2;
        std::cout << "Window resized: " << screenHeight << "x" << screenWidth << std::endl;
    }

    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.key == SDLK_ESCAPE)
        {
            isRunning = false;
        }
        if (event.key.key == SDLK_F11)
        {

            fullscreenEnabled = !fullscreenEnabled;
            if (!fullscreenEnabled)
            {
                SDL_SetWindowFullscreen(window, 0);
            }
            else
            {
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
            }
        }
        if (event.key.key == SDLK_F)
        {
            fpsIndex = (fpsIndex + 1) % 5;
            targetFPS = fpsOptions[fpsIndex];
            targetFrameTime = (targetFPS > 0) ? 1000.0 / targetFPS : 0.0;
            std::cout << "\nFPS set to "
                      << (targetFPS == 0 ? "∞" : std::to_string((int)targetFPS))
                      << std::endl;
        }
        if (event.key.key == SDLK_V)
        {
            vsyncEnabled = !vsyncEnabled;
            SDL_SetRenderVSync(renderer, vsyncEnabled ? 1 : 0);
        }
    }
}

void WindowHandler::UpdateTime()
{
    Uint64 now = SDL_GetTicksNS();
    deltaTime = (now - lastCounter) / 1'000'000'000.0;
    lastCounter = now;
    frameStart = now;
}

void WindowHandler::LimitFPS()
{
    if (!vsyncEnabled && targetFPS > 0)
    {
        Uint64 now = SDL_GetTicksNS();
        double targetNs = targetFrameTime * 1'000'000.0;
        double elapsed = now - frameStart;

        if (elapsed < targetNs)
            SDL_DelayNS((Uint64)(targetNs - elapsed));
    }
}

void WindowHandler::ShowDeltaTime()
{
    double fps = (deltaTime > 0.0) ? 1.0 / deltaTime : 0.0;
    std::cout << "\rDeltaTime: " << deltaTime
              << " s | FPS: " << (int)fps
              << " | VSync: " << (vsyncEnabled ? "ON " : "OFF")
              << "   " << std::flush;
}
