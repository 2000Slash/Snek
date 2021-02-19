#include <SDL2/SDL.h>
#include "GameObject.hpp"
#include <vector>
#include "Snek.hpp"
#include "Apple.hpp"
#include <SDL2/SDL_ttf.h>

class ObjectManager {
    private:
        std::vector<GameObject*> gameObjects;
        std::vector<GameObject::cell> allCells;
        Snek* snek;
        Apple* apple;
        int score = 0;
        bool displayGrid = false;
        SDL_Texture* backgroundTexture;
        SDL_Texture* scoreTexture;
        Uint32 primColor = 0xA2D049;
        Uint32 secColor = 0xA9D751;
        int scoreW, scoreH;
        TTF_Font *scoreFont;
        SDL_Renderer* renderer;
        void addScore(SDL_Renderer*);
    public:
        ObjectManager(SDL_Renderer*);
        ~ObjectManager();
        void render(SDL_Renderer*);
        void drawBackground(SDL_Renderer*);
        void drawGrid(SDL_Renderer*);
        bool update();
        void handleKey(SDL_Keycode);
        void addObject(GameObject*);
};