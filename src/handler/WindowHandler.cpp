
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "WindowHandler.h"
#include "JsonConfigHandler.h"
#include "TextureHandler.h"

WindowHandler::WindowHandler()
{

    JsonConfigHandler::Load();
    fullscreenEnabled = JsonConfigHandler::Get("fullscreen", false);
    vsyncEnabled = JsonConfigHandler::Get("vsync", false);
    screenWidth  = JsonConfigHandler::Get("width", 1280);
    screenHeight = JsonConfigHandler::Get("height", 720);
    JsonConfigHandler::Save();

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
    JsonConfigHandler::Load();
    JsonConfigHandler::Set("fullscreen", fullscreenEnabled);
    JsonConfigHandler::Set("vsync", vsyncEnabled);
    JsonConfigHandler::Set("width", screenWidth);
    JsonConfigHandler::Set("height", screenHeight);
    JsonConfigHandler::Save();

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
        double targetFrameTimeNs = 1'000'000'000.0 / targetFPS;
        double elapsed = now - frameStart;

        if (elapsed < targetFrameTimeNs){
            SDL_DelayNS((Uint64)(targetFrameTimeNs - elapsed));
        }


    }
//     else
//     {
//         Selleping sleep so that the CPU can relax
//         SDL_Delay(1);
//     }

}

// void WindowHandler::LimitFPS()
// {
//     if (!vsyncEnabled && targetFPS > 0)
//     {
//         Uint64 now = SDL_GetTicksNS();
//         double targetFrameTimeNs = 1'000'000'000.0 / targetFPS;
//         double elapsed = now - frameStart;

//         if (elapsed < targetFrameTimeNs){
//             Uint32 delayMs = static_cast<Uint32>((targetFrameTimeNs - elapsed) / 1'000'000.0);
//             SDL_Delay(delayMs);
//         }
//           // Busy-Wait für Restzeit
//         while ((SDL_GetTicksNS() - frameStart) < targetFrameTimeNs)
//         {
//             // Leere Schleife → CPU wartet aktiv
//         }
//     }
//     else
//     {
//         SDL_Delay(1);
//     }
// }




void WindowHandler::ShowDeltaTime()
{
    double fps = (deltaTime > 0.0) ? 1.0 / deltaTime : 0.0;
    std::cout << "\rDeltaTime: " << deltaTime
              << " s | FPS: " << (int)fps
              << " | VSync: " << (vsyncEnabled ? "ON " : "OFF")
              << "   " << std::flush;
}
