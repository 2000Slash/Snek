#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GameObject {
    public:
        virtual void render(SDL_Renderer *) = 0;
        virtual void update() = 0;
};