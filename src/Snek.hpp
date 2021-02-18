#pragma once
#include "GameObject.hpp"
#include <vector>
#include <tuple>

class Snek : public GameObject {
    private:
        int x, y;
        int direction, nextDirection;
        void renderSegment(int, int, SDL_Renderer*);
        void updateTail();
        void move();
        bool checkSelfCollision();
        struct segment;
        struct cell;
        std::vector<cell> cells;
        std::vector<segment> segments;
        SDL_Texture* headTexture;
        SDL_Surface* headSurface;
        SDL_Texture* segmentTexture;
        SDL_Surface* segmentSurface;
        SDL_Surface* debugSurface;
        SDL_Texture* debugTexture;
    public:
        Snek(SDL_Renderer*);
        ~Snek();
        void update() override;
        void changeDirection(int);
        std::tuple<int, int> getCoords();
        void render(SDL_Renderer *) override;
};