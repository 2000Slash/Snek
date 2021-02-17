#include <SDL2/SDL.h>
#include "GameObject.hpp"
#include <vector>
#include "Snek.hpp"

class ObjectManager {
    private:
        std::vector<GameObject*> gameObjects;
        Snek* snek;
    public:
        ObjectManager(SDL_Renderer*);
        void render(SDL_Renderer*);
        void drawBackground(SDL_Renderer*);
        void update();
        void handleKey(SDL_Keycode);
        void addObject(GameObject*);
};