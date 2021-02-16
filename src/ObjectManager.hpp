#include <SDL2/SDL.h>
#include "GameObject.hpp"
#include <vector>

class ObjectManager {
    private:
        std::vector<GameObject*> gameObjects;
    public:
        ObjectManager(SDL_Renderer*);
        void render(SDL_Renderer*);
        void update();
        void addObject(GameObject*);
};