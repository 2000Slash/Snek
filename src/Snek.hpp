#include "GameObject.hpp"

class Snek : GameObject {
    private:
        int direction;
        int x, y;
        SDL_Texture* texture;
        SDL_Surface* surface;
    public:
        Snek(SDL_Renderer*);
        ~Snek();
        void update() override;
        void render(SDL_Renderer *) override;
};