#include "Apple.hpp"
#include "Defaults.h"

void Apple::render(SDL_Renderer* renderer) {
    SDL_Rect dstrect;
    dstrect.x = x*SPRITE_WIDTH;
    dstrect.y = y*SPRITE_HEIGHT;
    dstrect.w = SPRITE_WIDTH;
    dstrect.h = SPRITE_HEIGHT;
    SDL_RenderCopy(renderer, appleTexture, NULL, &dstrect);
}

void Apple::update() {

}

void Apple::reposition(std::vector<GameObject::cell> freeCells) {
    cell c = freeCells.at(rand()%freeCells.size());
    x = c.x;
    y = c.y;
}

Apple::Apple(SDL_Renderer* renderer, int pX, int pY) {
    appleSurface = IMG_Load("data/Apple.png");
    appleTexture = SDL_CreateTextureFromSurface(renderer, appleSurface);
    x = pX;
    y = pY;
}

std::tuple<int, int> Apple::getCoords() {
    return std::tuple<int, int>(x, y);
}