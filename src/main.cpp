
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "BundleHandler.h"
#include "WindowHandler.h"
#include "ConfigInfo.h"

int main(int argc, char *argv[])
{
    initExeDir();
    std::cerr << exeDir << "\n";

    std::string bundlePath = "assets/bundle.bin";

    // Bundle load
    if (!BundleHandler::loadBundle(bundlePath))
    {
        return 1;
    }
    BundleHandler::printAllEntries();

    WindowHandler window;
    SDL_Event event;

    std::cout << PROJECT_NAME << "\n";
    std::cout << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH << "\n";

    std::cout << "Press ESC to quit\n";

    // BOX TEST
    float rectX = 0.0f;
    float rectY = 200.0f;
    float rectX2 = 0.0f;
    float rectY2 = 300.0f;

    float speed = 200.0f;

    int rectW = 100;
    int rectH = 100;

    while (window.IsRunning())
    {
        // --- DeltaTime ---
        window.UpdateTime();
        double dt = window.DeltaTime();

        // --- Event Handling ---
        while (SDL_PollEvent(&event))
        {
            window.HandleEvent(event);
        }

        // --- Fill Backgroundcolor ---
        SDL_SetRenderDrawColor(window.GetRenderer(), 0, 0, 255, 255);
        SDL_RenderClear(window.GetRenderer());

        // --- Render ---

        // BOX TEST
        rectX += speed * dt;
        if (rectX > 1640)
        {
            rectX = -rectW;
        }
        SDL_FRect rect;
        rect.x = rectX;
        rect.y = rectY;
        rect.w = 100.0f;
        rect.h = 100.0f;
        SDL_SetRenderDrawColor(window.GetRenderer(), 255, 0, 0, 255);
        SDL_RenderFillRect(window.GetRenderer(), &rect);

        // BOX TEST
        rectX2 += speed * 1.1 * dt;
        if (rectX2 > 1640)
        {
            rectX2 = -rectW;
        }
        SDL_FRect rect2;
        rect2.x = rectX2;
        rect2.y = rectY2;
        rect2.w = 100.0f;
        rect2.h = 100.0f;
        SDL_SetRenderDrawColor(window.GetRenderer(), 255, 230, 0, 255);
        SDL_RenderFillRect(window.GetRenderer(), &rect2);

        // --- Screen Update ---
        SDL_RenderPresent(window.GetRenderer());

        // --- FPS Limiter ---
        window.LimitFPS();

        // --- DeltaTime & FPS Anzeige ---
        window.ShowDeltaTime();
    }

    return 0;
}
