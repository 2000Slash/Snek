#include "ObjectManager.hpp"
#include "Snek.hpp"
#include "Defaults.h"
#include <iostream>
#include <algorithm>

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

    std::tuple<int, int> coords = snek->getCoords();
    int sx, sy;
    sx = std::get<0>(coords);
    sy = std::get<1>(coords);

    if(sx >= WIDTH/SPRITE_WIDTH || sx < 0 || sy >= HEIGHT/SPRITE_HEIGHT || sy < 0) {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    }

    if(apple->getCoords() == snek->getCoords()) {
        std::vector<GameObject::cell> snekCells = snek->getCollisionCells();
        std::vector<GameObject::cell> tmpCells(allCells);

        for(GameObject::cell c : snekCells) {
            tmpCells.erase(std::remove(tmpCells.begin(), tmpCells.end(), c));
        }
        apple->reposition(tmpCells);
        snek->increaseTail();
    }
}

void ObjectManager::drawBackground(SDL_Renderer* renderer) {
    if (displayGrid) {
        drawGrid(renderer);
    }
}

void ObjectManager::drawGrid(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for(int x = 0; x < WIDTH/SPRITE_WIDTH; x++) {
        SDL_RenderDrawLine(renderer, x*SPRITE_WIDTH, 0, x*SPRITE_WIDTH, HEIGHT/SPRITE_HEIGHT*SPRITE_HEIGHT);
    }
    for(int y = 0; y < HEIGHT/SPRITE_HEIGHT; y++) {
        SDL_RenderDrawLine(renderer, 0, y*SPRITE_HEIGHT, WIDTH/SPRITE_WIDTH*SPRITE_WIDTH, y*SPRITE_HEIGHT);
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

    int gridWidth = WIDTH/SPRITE_WIDTH;
    int gridHeight = HEIGHT/SPRITE_HEIGHT;
    for(int x = 0; x < gridWidth; x++) {
        for(int y = 0; y < gridHeight; y++) {
            GameObject::cell c;
            c.x = x;
            c.y = y;
            allCells.push_back(c);
        }
    }
}