#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameObject {
    public:
        virtual void render(SDL_Renderer *) = 0;
        virtual bool update() = 0;
        struct cell {
            int x, y;
            bool operator==(const cell& b) {
                return x == b.x && y == b.y;
            }
        };
};