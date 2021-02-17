#include <SDL2/SDL.h>        
#include <SDL2/SDL_image.h>
#include "Snek.hpp"
#include <iostream>
#include "ObjectManager.hpp"
#include "Defaults.h"

#ifdef __SWITCH__
#include <switch.h>
void changeFolder() {
    romfsInit();
    chdir("romfs:/");
}
#endif
 
SDL_Window* createWindow() { 
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    return SDL_CreateWindow("Snek",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
}

int main(int argc, char **argv)
{
    #ifdef __SWITCH__
    changeFolder()
    #endif
    SDL_Window* window = createWindow();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    ObjectManager manager(renderer);
    
    SDL_Event event;
    bool quit = false;
    double frameMs = 1000 / 60;
    while (!quit)
    {
        double startMs = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        manager.render(renderer);
        manager.update();
        SDL_RenderPresent(renderer);
        double endMs = SDL_GetTicks();
        double delayMs = frameMs - (endMs - startMs);
        if (delayMs > 0) {
            SDL_Delay(delayMs);
        }
    }
 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    IMG_Quit();
    SDL_Quit();
 
    return 0;
}