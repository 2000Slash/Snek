#include "ObjectManager.hpp"
#include "Snek.hpp"
#include "Defaults.h"
#include <iostream>
#include <algorithm>

#define JOY_A     0
#define JOY_B     1
#define JOY_X     2
#define JOY_Y     3
#define JOY_PLUS  10
#define JOY_LEFT  12
#define JOY_UP    13
#define JOY_RIGHT 14
#define JOY_DOWN  15

void ObjectManager::render(SDL_Renderer* renderer) {
    drawBackground(renderer);
    for(GameObject* object: gameObjects) {
        object->render(renderer);
    }
    SDL_Rect rect;
    rect.x = WIDTH/2-scoreW/2;
    rect.y = HEIGHT-25;
    rect.w = scoreW;
    rect.h = scoreH;
    SDL_RenderCopy(renderer, scoreTexture, NULL, &rect);
}

void ObjectManager::addScore(SDL_Renderer* renderer) {
    score++;
    SDL_Color color = {255, 255, 255};
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);
    SDL_Surface* scoreSurface = TTF_RenderText_Blended(scoreFont, scoreText, color);
    scoreW = scoreSurface->w;
    scoreH = scoreSurface->h;
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FreeSurface(scoreSurface);
}

bool ObjectManager::update() {
    for(GameObject* object: gameObjects) {
        if (object->update() == false) {
            return false;
        }
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
        addScore(renderer);
        std::vector<GameObject::cell> snekCells = snek->getCollisionCells();
        std::vector<GameObject::cell> tmpCells(allCells);

        for(GameObject::cell c : snekCells) {
            tmpCells.erase(std::remove(tmpCells.begin(), tmpCells.end(), c));
        }
        apple->reposition(tmpCells);
        snek->increaseTail();
    }
    return true;
}

void ObjectManager::drawBackground(SDL_Renderer* renderer) {
    if (displayGrid) {
        drawGrid(renderer);
    } else {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
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

void ObjectManager::handleButton(int button) {
    switch(button) {
        case JOY_UP:
            snek->changeDirection(0);
            break;
        case JOY_RIGHT:
            snek->changeDirection(1);
            break;
        case JOY_DOWN:
            snek->changeDirection(2);
            break;
        case JOY_LEFT:
            snek->changeDirection(3);
            break;
    }
}

void ObjectManager::addObject(GameObject* object) {
    gameObjects.push_back(object);
}

ObjectManager::ObjectManager(SDL_Renderer* renderer) {
    this->renderer = renderer;
    snek = new Snek(renderer);
    apple = new Apple(renderer, 5, 5);
    addObject(apple);
    addObject(snek);

    SDL_Color color = {255, 255, 255};
    SDL_Surface* surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 255);

    SDL_FillRect(surface, NULL, 0x654321);
    scoreFont = TTF_OpenFont("data/OpenSans/OpenSans-SemiBold.ttf", 20);
    if(!scoreFont) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    SDL_Surface* scoreSurface = TTF_RenderText_Blended(scoreFont, "Score: 0", color);
    scoreW = scoreSurface->w;
    scoreH = scoreSurface->h;
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FreeSurface(scoreSurface);


    for(int x = 0; x < WIDTH/SPRITE_WIDTH; x++) {
        for(int y = 0; y < HEIGHT/SPRITE_HEIGHT; y++) {
            SDL_Rect rect;
            rect.x = x*SPRITE_WIDTH;
            rect.y = y*SPRITE_HEIGHT;
            rect.w = SPRITE_WIDTH;
            rect.h = SPRITE_HEIGHT;
            if((x + y) % 2 == 0) {
                SDL_FillRect(surface, &rect, primColor);
            } else {
                SDL_FillRect(surface, &rect, secColor);
            }
        }
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

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

ObjectManager::~ObjectManager() {
    SDL_DestroyTexture(backgroundTexture);
}