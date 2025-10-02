#include "EventHandler.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "AppWindow.h"
#include <unordered_set>
#include <iostream>

SDL_Event EventHandler::event;
std::unordered_set<SDL_Keycode> EventHandler::keyboardCurrentAction;
std::unordered_set<SDL_Keycode> EventHandler::keyboardLastAction;
std::unordered_set<SDL_Keycode> EventHandler::mouseCurrentAction;
std::unordered_set<SDL_Keycode> EventHandler::mouseLastAction;
int EventHandler::mouseX = 0;
int EventHandler::mouseY = 0;
bool EventHandler::mouseMove = false;

void EventHandler::AllScans()
{

    keyboardLastAction = keyboardCurrentAction;
    mouseLastAction = mouseCurrentAction;

    mouseMove = false;

    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_EVENT_MOUSE_MOTION) {
      
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            mouseMove = true;
            // std::cout << "Mouse moved: " << mouseX << ", " << mouseY << "\n";
        }
        
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            switch (event.button.button)
            {
                case SDL_BUTTON_LEFT:
                    mouseCurrentAction.insert(event.button.button);
                    //std::cout << "Left mouse button pressed\n";
                    break;
                case SDL_BUTTON_RIGHT:
                    mouseCurrentAction.insert(event.button.button);
                    //std::cout << "Right mouse button pressed\n";
                    break;
                case SDL_BUTTON_MIDDLE:
                    mouseCurrentAction.insert(event.button.button);
                    //std::cout << "Middle mouse button pressed\n";
                    break;
            }
        }

        // ! Mouse extra button prüfen
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            switch (event.button.button)
            {
                case SDL_BUTTON_LEFT:
                    mouseCurrentAction.erase(event.button.button);
                    break;
                case SDL_BUTTON_RIGHT:
                    mouseCurrentAction.erase(event.button.button);
                    break;
                case SDL_BUTTON_MIDDLE:
                    mouseCurrentAction.erase(event.button.button);
                    break;
            }
        }

        // ! Mouse Wheel Prüfen
        if (event.type == SDL_EVENT_MOUSE_WHEEL)
        {
            
            std::cout << "Mouse wheel scrolled: "
                    << "X: " << event.wheel.x
                    << ", Y: " << event.wheel.y << "\n";

            if (event.wheel.y > 0) std::cout << "Scrolled UP\n";
            if (event.wheel.y < 0) std::cout << "Scrolled DOWN\n";
            if (event.wheel.x > 0) std::cout << "Scrolled RIGHT\n";
            if (event.wheel.x < 0) std::cout << "Scrolled LEFT\n";
        }

          // ! Keyboard Prüfen klein groß und feststelltaste
        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            keyboardCurrentAction.insert(event.key.key);
            //std::cout << "Key Pressed: " << SDL_GetKeyName(event.key.key)<< "\n";
        }
        if (event.type == SDL_EVENT_KEY_UP)
        {
            keyboardCurrentAction.erase(event.key.key);
            //std::cout << "Key released: " << SDL_GetKeyName(event.key.key)<< "\n";
        }
        if (event.type == SDL_EVENT_QUIT)
        {
            SDL_Quit();
            std::exit(0);
        }
    }
}

bool EventHandler::KeyboardCheckPressed(SDL_Keycode key)
{
    return keyboardCurrentAction.count(key) && !keyboardLastAction.count(key);
}

bool EventHandler::KeyboardCheckReleased(SDL_Keycode key)
{
    return !keyboardCurrentAction.count(key) && keyboardLastAction.count(key);
}

bool EventHandler::KeyboardCheckHeld(SDL_Keycode key)
{
    return keyboardCurrentAction.count(key) && keyboardLastAction.count(key);
}

bool EventHandler::MouseCheckPressed(Uint8 button) {
    return mouseCurrentAction.count(button) && !mouseLastAction.count(button);
}

bool EventHandler::MouseCheckReleased(Uint8 button) {
    return !mouseCurrentAction.count(button) && mouseLastAction.count(button);
}

bool EventHandler::MouseCheckHeld(Uint8 button) {
    return mouseCurrentAction.count(button) && mouseLastAction.count(button);
}

bool EventHandler::MouseCheckMoved()
{
    return mouseMove;
}

int EventHandler::MouseX(){
    return mouseX;
}

int EventHandler::MouseY(){
    return mouseY;
}