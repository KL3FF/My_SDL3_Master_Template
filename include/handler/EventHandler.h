#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class EventHandler
{
private:
    /* data */
public:
    EventHandler() = delete;

    ~EventHandler() = delete;

    static SDL_Event event;

    static void AllScans();
   
};
