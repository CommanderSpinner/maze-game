#pragma once

#include "Entity.hpp"
#include "InputManager.hpp"
#include "Global.hpp"

class Player :  public Entity {
private: 
    InputManager& input;

    void handleInput() {

    }
public:
    Player(InputManager& im) : Entity(Global::defaultTexture), input(im) {
        setTexture(Global::playerTexturePath);

    }
    void update(float deltaTime) override {
        // todo: add here code for player movement based on what input manager passes
        handleInput();
        Entity::update(deltaTime);
    }
    
};