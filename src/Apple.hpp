#include "GameObject.hpp"
#include <tuple>
#include <vector>

class Apple : public GameObject {
    private:
        SDL_Texture* appleTexture;
        SDL_Surface* appleSurface;
        int x, y;
    public:
        void reposition(std::vector<cell>);
        void render(SDL_Renderer *) override;
        bool update() override;
        Apple(SDL_Renderer *, int, int);
        std::tuple<int, int> getCoords();
};