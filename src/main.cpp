#include <SDL2/SDL.h>        
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
#ifdef __SWITCH__
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_JoystickOpen(0);
#endif
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    return SDL_CreateWindow("Snek",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
}

int main(int argc, char **argv)
{
    #ifdef __SWITCH__
    changeFolder();
    #endif
    SDL_Window* window = createWindow();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    ObjectManager manager(renderer);
    
    SDL_Event event;
    bool quit = false;
    bool update = true;
    double frameMs = 1000 / 60;
    while (!quit)
    {
        double startMs = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
#ifdef __SWITCH__
                case SDL_JOYBUTTONDOWN: {
                    int button = event.jbutton.button;
                    manager.handleButton(button);
                    break;
                }
#else
                case SDL_KEYDOWN: {
                    SDL_Keysym key = event.key.keysym;
                    manager.handleKey(key.sym);
                    break;
                }
#endif
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 101, 67, 33, 255);
        SDL_RenderClear(renderer);
        manager.render(renderer);
        if(update) {
            update = manager.update();
        }
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
    TTF_Quit();
 
    return 0;
}