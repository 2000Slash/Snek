#include "ObjectManager.hpp"
#include "Snek.hpp"
#include <iostream>

void ObjectManager::render(SDL_Renderer* renderer) {
    for(GameObject* object: gameObjects) {
        object->render(renderer);
    }
}

void ObjectManager::update() {
    for(GameObject* object: gameObjects) {
        object->update();
    }
}
 
void ObjectManager::addObject(GameObject* object) {
    gameObjects.push_back(object);
}

ObjectManager::ObjectManager(SDL_Renderer* renderer) {
    addObject(new Snek(renderer));
}