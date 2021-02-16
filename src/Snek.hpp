#include "GameObject.hpp"

class Snek : public GameObject {
    private:
        int direction = 2;
        int x, y;
        SDL_Texture* texture;
        SDL_Surface* surface;
    public:
        Snek(SDL_Renderer*);
        ~Snek();
        void update() override;
        void render(SDL_Renderer *) override;
};