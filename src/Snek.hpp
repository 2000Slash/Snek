#include "GameObject.hpp"

class Snek : GameObject {
    private:
        SDL_Texture* texture;
        SDL_Surface* surface;
    public:
        Snek(SDL_Renderer*);
        ~Snek();
        void render(SDL_Renderer *) override;
};