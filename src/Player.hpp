#pragma once

#include "Entity.hpp"
#include "InputManager.hpp"

class Player :  public Entity {
private: 
    InputManager& input;
public:
    Player(InputManager& im) : input(im) {}
    void update(float deltaTime) override {
        // todo: add here code for player movement based on what input manager passes
        Entity::update(deltaTime);
    }
};