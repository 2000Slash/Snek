#include "ObjectManager.hpp"
#include "Snek.hpp"
#include "Defaults.h"
#include <iostream>

void ObjectManager::render(SDL_Renderer* renderer) {
    drawBackground(renderer);
    for(GameObject* object: gameObjects) {
        object->render(renderer);
    }
}

void ObjectManager::update() {
    for(GameObject* object: gameObjects) {
        object->update();
    }

    if(apple->getCoords() == snek->getCoords()) {
        apple->reposition();
        snek->increaseTail();
    }
}

void ObjectManager::drawBackground(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for(int x = 0; x < 19; x++) {
        SDL_RenderDrawLine(renderer, x*SPRITE_WIDTH, 0, x*SPRITE_WIDTH, HEIGHT);
    }
    for(int y = 0; y < 11; y++) {
        SDL_RenderDrawLine(renderer, 0, y*SPRITE_HEIGHT, WIDTH, y*SPRITE_HEIGHT);
    }
}
 
void ObjectManager::handleKey(SDL_Keycode code) {
    switch(code) {
        case SDLK_UP:
        case SDLK_w:
            snek->changeDirection(0);
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            snek->changeDirection(1);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            snek->changeDirection(2);
            break;
        case SDLK_LEFT:
        case SDLK_a:
            snek->changeDirection(3);
            break;
    }
}

void ObjectManager::addObject(GameObject* object) {
    gameObjects.push_back(object);
}

ObjectManager::ObjectManager(SDL_Renderer* renderer) {
    snek = new Snek(renderer);
    apple = new Apple(renderer, 5, 5);
    addObject(apple);
    addObject(snek);
}