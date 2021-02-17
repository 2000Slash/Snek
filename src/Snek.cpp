#include "Snek.hpp"
#include <iostream>
#include "Defaults.h"

struct Snek::segment {
    int x, y;
    int life;
};

// iterate through all segments and draw them to the screen
void Snek::render(SDL_Renderer *renderer) {
    for (segment seg: segments) {
        int realX = seg.x;
        int realY = seg.y;
        renderSegment(realX, realY, renderer);
    }
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = SPRITE_WIDTH;
    dstrect.h = SPRITE_HEIGHT;
    SDL_RenderCopyEx(renderer, headTexture, NULL, &dstrect, (direction-1)*90, NULL, SDL_FLIP_NONE);
}

// Draw a single segment to the screen
void Snek::renderSegment(int x, int y, SDL_Renderer* renderer) {
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = SPRITE_WIDTH;
    dstrect.h = SPRITE_HEIGHT;
    SDL_RenderCopy(renderer, segmentTexture, NULL, &dstrect);
}

void Snek::update() {
    static int time = 0;
    updateTail();
    move();
    time++;
    if (time % 60 == 0) {
        direction++;
    }
}

void Snek::move() {
    switch(direction) {
        case 0:
            y-=SPEED;
            break;
        case 1:
            x+=SPEED;
            break;
        case 2:
            y+=SPEED;
            break;
        case 3:
            x-=SPEED;
            break;
    }
}

void Snek::updateTail() {
    for(std::vector<segment>::iterator i = segments.begin(); i != segments.end(); i++) {
        i->life-=1;
        if (i->life <=0) {
            segments.erase(i);
            i--;
        }
    }
    segment seg;
    seg.x = x;
    seg.y = y;
    seg.life = 120;
    segments.push_back(seg);
}

Snek::Snek(SDL_Renderer* renderer) {
    headSurface = IMG_Load("data/Snek-head.png");
    headTexture = SDL_CreateTextureFromSurface(renderer, headSurface);
    segmentSurface = IMG_Load("data/Snek-segment.png");
    segmentTexture = SDL_CreateTextureFromSurface(renderer, segmentSurface);

    x = WIDTH/2;
    y = HEIGHT/2;
    direction = 1;

    for(int i = 0; i < 120; i++) {
        segment seg;
        seg.y = y;
        seg.x = x-i*2;
        seg.life = 120-i;
        segments.push_back(seg);
    }
}

Snek::~Snek() {
    SDL_FreeSurface(headSurface);
    SDL_FreeSurface(segmentSurface);
    SDL_DestroyTexture(headTexture);
    SDL_DestroyTexture(segmentTexture);
}