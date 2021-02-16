#include "Snek.hpp"

void Snek::render(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

Snek::Snek(SDL_Renderer* renderer) {
    surface = IMG_Load("Snek.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

Snek::~Snek() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}