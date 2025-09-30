
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

//int argc, char *argv[]
int main()
{
    init();

    std::cerr << exeDir << "\n";
    // Bundle load
    if (!BundleAssetsHandler::LoadBundle())
    {
        return 1;
    }
    BundleAssetsHandler::PrintAllEntries();

    AppWindow window;
    SDL_Event event;
    TextureManager::InitPlaceholder(window.GetRenderer());

    std::cout << PROJECT_NAME << "\n";
    std::cout << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH << "\n";

    std::cout << "Press ESC to quit\n";

    // BOX TEST
    float rectX = 0.0f;
    float rectY = 200.0f;
    float rectX2 = 0.0f;
    float rectY2 = 300.0f;
    float speed = 5.0f;



    // ! TEST PLAYER
    InstanceHandler::AddInstance(new Player(0.0f,0.0f,0.0f));

    while (window.IsRunning())
    {
        // --- DeltaTime ---
        window.UpdateTime();
        double dt = window.DeltaTime()*60;
        // --- Event Handling ---
        while (SDL_PollEvent(&event))
        {
            window.HandleEvent(event);
        }
        // --- Update ---
        InstanceHandler::AllUpdate(dt);


        // --- Render ---
        SDL_SetRenderDrawColor(&window.GetRenderer(), 0, 0, 255, 255);
        SDL_RenderClear(&window.GetRenderer());
        InstanceHandler::AllDraw(window.GetRenderer());

        // ! BOX TEST
        rectX2 += speed * 1.5 * dt;
        if (rectX2 > 1640)
        {
            rectX2 = -100;
        }
        SDL_FRect src2 = {0, 0, 128, 128};
        SDL_FRect dst2 = {rectX2, rectY2, 128, 128};
        SDL_RenderTexture(&window.GetRenderer(), TextureManager::GetTexture("test2", "assets/sprites/high/hero/test2.png"), &src2, &dst2);

        // ! BOX TEST
        rectX += speed * dt;
        if (rectX > 1640)
        {
            rectX = -100;
        }
        SDL_FRect src = {0, 0, 128, 128};
        SDL_FRect dst = {rectX, rectY, 128, 128};
        SDL_RenderTexture(&window.GetRenderer(), TextureManager::GetTexture("test3", "assets/sprites/high/hero/test3.bmp"), &src, &dst);

        // --- Screen Update ---
        SDL_RenderPresent(&window.GetRenderer());

        // --- FPS Limiter ---
        // window.LimitFPS();

        // --- DeltaTime & show fps ---
        // window.ShowDeltaTime();

        // --- Lazy Loader for Textures ---
        TextureManager::TextureProcessUnload();
        TextureManager::TextureLazyLoad(window.GetRenderer());
    }

    TextureManager::ClearAll();
    BundleAssetsHandler::ClearAllFiles();
    return 0;
}
