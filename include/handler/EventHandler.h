#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <unordered_set>
class EventHandler
{
private:
    /* data */
public:
    EventHandler() = delete;
    ~EventHandler() = delete;

    static SDL_Event event;
    static std::unordered_set<SDL_Keycode> keyboardCurrentAction;
    static std::unordered_set<SDL_Keycode> keyboardLastAction;
    static std::unordered_set<SDL_Keycode> mouseCurrentAction;
    static std::unordered_set<SDL_Keycode> mouseLastAction;
    static int mouseX;
    static int mouseY;
    static bool mouseMove;

    static void AllScans();

    static bool KeyboardCheckPressed(SDL_Keycode key);
    static bool KeyboardCheckReleased(SDL_Keycode key);
    static bool KeyboardCheckHeld(SDL_Keycode key);

    static bool MouseCheckPressed(Uint8 button);
    static bool MouseCheckReleased(Uint8 button);
    static bool MouseCheckHeld(Uint8 button);

    static bool MouseWheelUp(SDL_Keycode key);
    static bool MouseWheelDown(SDL_Keycode key);

    static bool MouseCheckMoved();
    static int MouseX();
    static int MouseY();
};
