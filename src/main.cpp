#include <SDL3/SDL.h>
#include <iostream>
#include "WindowHandler.h"
#include "InstanceHandler.h"
int main(int argc, char *argv[])
{

    WindowHandler window("An SDL3 window", 640, 480, SDL_WINDOW_RESIZABLE);

    SDL_Event event;

    std::cout << "Press F to switch FPS (30/60/120/144/∞)\n";
    std::cout << "Press V to toggle VSync\n";
    std::cout << "Press F11 to toggle Fullscrenn\n";
    std::cout << "Press ESC to quit\n";

    while (window.IsRunning())
    {

        // --- DeltaTime ---
        window.UpdateTime();

        // --- Update ---

        while (SDL_PollEvent(&event))
        {
            window.HandleEvent(event);
        }
        // InstanceHandler::AllUpdate(window.DeltaTime());

        // --- Render ---
        SDL_SetRenderDrawColor(window.GetRenderer(), 0, 0, 255, 255);
        SDL_RenderClear(window.GetRenderer());
        SDL_RenderPresent(window.GetRenderer());

        // InstanceHandler::AllDraw();

        // --- FPS Limiter ---
        window.LimitFPS();

        // --- Show FPS ---
        window.ShowDeltaTime();
    }

    return 0;
}