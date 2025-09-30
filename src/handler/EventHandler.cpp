#include "EventHandler.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "AppWindow.h"

SDL_Event EventHandler::event;

void EventHandler::AllScans()
{
    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_EVENT_QUIT)
        {
            SDL_Quit();
            std::exit(0);
        }

        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
        {
            SDL_Quit();
            std::exit(0);
        }
    }
}
