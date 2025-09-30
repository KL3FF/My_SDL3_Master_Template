
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "BundleAssetsHandler.h"
#include "AppWindow.h"
#include "AppInfo.h"
#include "TextureHandler.h"
#include "InstanceHandler.h"
#include "GuiHandler.h"

// int argc, char *argv[]
int main()
{
    init();

    if (!BundleAssetsHandler::LoadBundle())
    {
        return 1;
    }
    // BundleAssetsHandler::PrintAllEntries();

    AppWindow window;
   
    TextureManager::InitPlaceholder(window.GetRenderer());

    // std::cout << PROJECT_NAME << "\n";
    // std::cout << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH << "\n";

    // std::cout << "Press ESC to quit\n";

    // ! TEST GUI
    GuiHandler::AddInstance(new StartGui(0.0f, 0.0f, 0.0f));

    // ! TEST PLAYER
    InstanceHandler::AddInstance(new Player(window.GetRenderer(), 0.0f, 0.0f, 0.0f));
    InstanceHandler::AddInstance(new Player(window.GetRenderer(), 128.0f, 128.0f, 0.0f));
    InstanceHandler::AddInstance(new Player(window.GetRenderer(), 256.0f, 256.0f, 0.0f));

    SDL_Event event;
    while (window.IsRunning())
    {
        // --- DeltaTime ---
        window.UpdateTime();
        double dt = window.DeltaTime() * 60;
        // --- Event Handling ---
        while (SDL_PollEvent(&event))
        {
            window.HandleEvent(event);
        }
        
        // --- Update ---
        InstanceHandler::AllUpdate(window.GetRenderer(), dt);

        // --- Set Backgroudcolor ---
        SDL_SetRenderDrawColor(&window.GetRenderer(), 0, 0, 255, 255);

        // --- Clear Render ---
        SDL_RenderClear(&window.GetRenderer());

        // --- Draw on Render ---
        InstanceHandler::AllDraw(window.GetRenderer());

        // --- Screen Update ---
        SDL_RenderPresent(&window.GetRenderer());

        // --- FPS Limiter ---
        window.LimitFPS();

        // --- DeltaTime & show fps ---
        window.ShowDeltaTime();

        // --- Lazy Loader for Textures ---
        TextureManager::TextureLazyUnloader();
        TextureManager::TextureLazyLoader(window.GetRenderer());
    }

    TextureManager::ClearAll();
    BundleAssetsHandler::ClearAllFiles();
    return 0;
}
