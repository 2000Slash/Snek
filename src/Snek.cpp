#include "Snek.hpp"
#include <iostream>
#include <cmath>
#include <cmath>

struct Snek::segment {
    int x, y;
    int life;
};

std::vector<GameObject::cell> Snek::getCollisionCells() {
    return cells;
}

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

    if (debug) {
        for(cell c: cells) {
            SDL_Rect dstrect;
            dstrect.x = c.x*70;
            dstrect.y = c.y*70;
            dstrect.w = SPRITE_WIDTH;
            dstrect.h = SPRITE_HEIGHT;
            SDL_RenderCopy(renderer, debugTexture, NULL, &dstrect);
        }
    }
}

void Snek::changeDirection(int pDirection) {
    // check if we chose a direction that is opposite to our current.
    // I do this by making sure the x component flips from 0 to 1 and vice versa.

    // First calculate degrees
    int oldDeg = this->direction * 90;
    int newDeg = pDirection * 90;

    // Calculate the x component. C++ sin only accepts rads.
    // Also we have to floor because of precision errors.
    double newSin = floor(sin(newDeg * M_PI/ 180));
    double oldSin = floor(sin(oldDeg * M_PI/ 180));

    // if the new direction has the same abs sin as the old, we know that we specified the opposite direction.
    // If that is not the case we can set the direction to the new one.
    if (abs(oldSin) != abs(newSin)) {
        this->nextDirection = pDirection;
    }
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
    // change direction if we are centered at a cell
    if (direction != nextDirection && x % 70 <= 5 && y % 70 <= 5) {
        direction = nextDirection;
        x = x / 70 * 70;
        y = y / 70 * 70;
    }
    updateTail();
    move();
    checkSelfCollision();
}

bool Snek::checkSelfCollision() {
    // We iterate over all cells but not the first one. The first one will always be the cell we are currently in.
    for(std::vector<cell>::iterator i = cells.begin(); i < cells.end()-1; i++) {
        cell c = *i;
        if (c.x == round(x/70.0) && c.y == round(y/70.0) ) {
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
            return false;
        }
    }
    return true;
}

void Snek::move() {
    switch(direction) {
        case 0:
            y-=speed;
            break;
        case 1:
            x+=speed;
            break;
        case 2:
            y+=speed;
            break;
        case 3:
            x-=speed;
            break;
    }

    if (cells.back().x != round(x/70.0) || cells.back().y != round(y/70.0)) {
        cell currentCell;
        currentCell.x = round(x/70.0);
        currentCell.y = round(y/70.0);
        cells.erase(cells.begin());
        cells.push_back(currentCell);
    }
}

void Snek::increaseTail() {
    // First calculate the difference in the life variable
    length++;
    int oldLife = life;
    life = (SPRITE_WIDTH / speed) * (length-1);
    int deltaLife = life - oldLife;

    // apply the difference to each segment
    for (segment& seg: segments) {
        seg.life += deltaLife;
    }

    // Now duplicate the the collision cell at the end of the snake
    cells.insert(cells.begin(), *cells.begin());
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
    seg.life = life;
    segments.push_back(seg);
}

std::tuple<int, int> Snek::getCoords() {
    return std::tuple<int, int>(round(x/70.0), round(y/70.0));
}

Snek::Snek(SDL_Renderer* renderer) {
    headSurface = IMG_Load("data/Snek-head.png");
    headTexture = SDL_CreateTextureFromSurface(renderer, headSurface);
    segmentSurface = IMG_Load("data/Snek-segment.png");
    segmentTexture = SDL_CreateTextureFromSurface(renderer, segmentSurface);

    x = 9*70;
    y = 5*70;
    direction = 1;
    nextDirection = 1;

    speed = 3;
    length = 3;
    life = (SPRITE_WIDTH / speed) * (length-1);

    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
    debugSurface = SDL_CreateRGBSurface(0, SPRITE_WIDTH, SPRITE_HEIGHT, 32, rmask, gmask, bmask, amask);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = SPRITE_WIDTH;
    rect.h = SPRITE_HEIGHT;
    SDL_FillRect(debugSurface, &rect, SDL_MapRGBA(debugSurface->format, 0xEA, 0x5A, 0x53, 0x80));
    debugTexture = SDL_CreateTextureFromSurface(renderer, debugSurface);

    for(int i = 0; i < length; i++) {
        cell currentCell;
        currentCell.x = round(x/70.0)-life*speed/70-1+i;
        currentCell.y = round(y/70.0);
        cells.push_back(currentCell);
    }

    for(int i = 0; i < life*speed; i++) {
        segment seg;
        seg.y = y;
        seg.x = x-i*speed;
        seg.life = life-i;
        segments.push_back(seg);
    }
}

Snek::~Snek() {
    SDL_FreeSurface(headSurface);
    SDL_FreeSurface(segmentSurface);
    SDL_DestroyTexture(headTexture);
    SDL_DestroyTexture(segmentTexture);
}