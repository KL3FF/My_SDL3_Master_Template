
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "AppWindow.h"
#include "WindowConfig.h"
#include "TextureHandler.h"

AppWindow::AppWindow()
{

    WindowConfig::LoadConfig();

    SDL_Init(SDL_INIT_VIDEO);
    
    window = SDL_CreateWindow(title, WindowConfig::getScreenWidth(), WindowConfig::getScreenHeight(), flags);
    
    renderer = SDL_CreateRenderer(window, NULL);
    
    SDL_SetRenderVSync(renderer, WindowConfig::isVSyncEnabled() ? 1 : 0);

    if (!WindowConfig::isFullscreen())
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

AppWindow::~AppWindow()
{
    WindowConfig::SaveConfig();

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


void AppWindow::HandleEvent(const SDL_Event &event)
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
        WindowConfig::setScreenHeight(event.window.data2);
        WindowConfig::setScreenWidth(event.window.data1);
        std::cout << "Window resized: " << WindowConfig::getScreenWidth() << "x" << WindowConfig::getScreenHeight() << std::endl;
    }
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.key == SDLK_ESCAPE)
        {
            isRunning = false;
        }
        if (event.key.key == SDLK_F11)
        {
            

            WindowConfig::setFullscreen(!WindowConfig::isFullscreen());
            if (!WindowConfig::isFullscreen())
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
            
            WindowConfig::setFpsIndex((WindowConfig::getFpsIndex() + 1) % 5);
            std::cout << "\nFPS set to "
                      << (WindowConfig::getTargetFps() == 0 ? "∞" : std::to_string((int)WindowConfig::getTargetFps()))
                      << std::endl;
        }
        if (event.key.key == SDLK_V)
        {
            WindowConfig::setVSync(!WindowConfig::isVSyncEnabled());
            SDL_SetRenderVSync(renderer, WindowConfig::isVSyncEnabled() ? 1 : 0);
        }
    }
}

void AppWindow::UpdateTime()
{
    Uint64 now = SDL_GetTicksNS();
    deltaTime = (now - lastCounter) / 1'000'000'000.0;
    lastCounter = now;
    frameStart = now;
}

void AppWindow::LimitFPS()
{
    
    if (!WindowConfig::isVSyncEnabled() && WindowConfig::getTargetFps() > 0)
    {
        Uint64 now = SDL_GetTicksNS();
        double targetFrameTimeNs = 1'000'000'000.0 / WindowConfig::getTargetFps();
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

void AppWindow::ShowDeltaTime()
{
    double fps = (deltaTime > 0.0) ? 1.0 / deltaTime : 0.0;
    std::cout << "\rDeltaTime: " << deltaTime
              << " s | FPS: " << (int)fps
              << " | VSync: " << (WindowConfig::isVSyncEnabled() ? "ON " : "OFF")
              << "   " << std::flush;
}








// void AppWindow::LimitFPS()
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

