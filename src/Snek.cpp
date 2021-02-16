#include "Snek.hpp"

void Snek::render(SDL_Renderer *renderer) {
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = 82;
    dstrect.h = 64;
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void Snek::update() {
    switch(direction) {
        case 0:
            y -= 2;
            break;
        case 1:
            x += 2;
            break;
        case 2:
            y += 2;
            break;
        case 3:
            x -= 2;
            break;
    }
}

Snek::Snek(SDL_Renderer* renderer) {
    x = 0;
    y = 0;
    surface = IMG_Load("data/Snek.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

Snek::~Snek() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}