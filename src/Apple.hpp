#include "GameObject.hpp"
#include <tuple>

class Apple : public GameObject {
    private:
        SDL_Texture* appleTexture;
        SDL_Surface* appleSurface;
        int x, y;
    public:
        void render(SDL_Renderer *) override;
        void update() override;
        Apple(SDL_Renderer *, int, int);
        std::tuple<int, int> getCoords();
};