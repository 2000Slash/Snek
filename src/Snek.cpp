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
    x += 2;
}

Snek::Snek(SDL_Renderer* renderer) {
    x = 0;
    y = 0;
    surface = IMG_Load("Snek.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

Snek::~Snek() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}