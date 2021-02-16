#include <SDL2/SDL.h>        
#include <SDL2/SDL_image.h>
#include "Snek.hpp"
 
SDL_Window* createWindow() { 
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    return SDL_CreateWindow("Snek",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
}

int main(int argc, char ** argv)
{
    SDL_Window* window = createWindow();
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    Snek snek(renderer);
    
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
        snek.render(renderer);
        SDL_RenderPresent(renderer);
    }
 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    IMG_Quit();
    SDL_Quit();
 
    return 0;
}