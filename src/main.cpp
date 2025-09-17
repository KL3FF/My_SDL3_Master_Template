#include "config.h"
#include <SDL3/SDL.h>
#include <iostream>
#include "WindowHandler.h"

int main(int argc, char *argv[])
{
    WindowHandler window;
    SDL_Event event;

    std::cout << "Press ESC to quit\n";

    // BOX TEST
    float rectX = 0.0f;
    float rectY = 200.0f;
    float speed = 200.0f; 

    int rectW = 50;
    int rectH = 50;

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
        SDL_SetRenderDrawColor(window.GetRenderer(), 0, 0, 255, 255); // Hintergrund
        SDL_RenderClear(window.GetRenderer());


        // --- Render ---


        // BOX TEST
        rectX += speed * dt;
        if (rectX > 640){
            rectX = -rectW;
        }
        SDL_FRect rect;
        rect.x = rectX;
        rect.y = rectY;
        rect.w = 50.0f;
        rect.h = 50.0f;
        SDL_SetRenderDrawColor(window.GetRenderer(), 255, 0, 0, 255);
        SDL_RenderFillRect(window.GetRenderer(), &rect);



        // --- Screen Update ---
        SDL_RenderPresent(window.GetRenderer());

        // --- FPS Limiter ---
        window.LimitFPS();

        // --- DeltaTime & FPS Anzeige ---
        window.ShowDeltaTime();
    }

    return 0;
}
