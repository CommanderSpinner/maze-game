#pragma once

#include "Entity.hpp"
#include "InputManager.hpp"

class Player :  public Entity {
private: 
    InputManager& input;

    void handleInput() {

    }
public:
    Player(InputManager& im, std::string texturePath) : input(im) {
        setTexture(texturePath);

    }
    void update(float deltaTime) override {
        // todo: add here code for player movement based on what input manager passes
        handleInput();
        Entity::update(deltaTime);
    }
    
};