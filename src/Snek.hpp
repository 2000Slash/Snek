#pragma once
#include "GameObject.hpp"
#include <vector>

class Snek : public GameObject {
    private:
        int x, y;
        int direction, nextDirection;
        void renderSegment(int, int, SDL_Renderer*);
        void updateTail();
        void move();
        struct segment;
        std::vector<segment> segments;
        SDL_Texture* headTexture;
        SDL_Surface* headSurface;
        SDL_Texture* segmentTexture;
        SDL_Surface* segmentSurface;
    public:
        Snek(SDL_Renderer*);
        ~Snek();
        void update() override;
        void changeDirection(int);
        void render(SDL_Renderer *) override;
};