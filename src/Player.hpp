#pragma once

#include "Character.hpp"
#include "InputManager.hpp"
#include "Global.hpp"

class Player :  public Character {
private: 
    InputManager& input;

    void handleInput() {
        if (input.isMovingDown()) {
            movement.y += speed;
        }

        if (input.isMovingUp()) {
            movement.y -= speed;
        }

        if (input.isMovingLeft()) {
            movement.x -= speed;
            
        }

        if (input.isMovingRight()) {        
            movement.x += speed;
            
        }


    }
public:
    Player(InputManager& im) : input(im) {
        setTexture(Global::playerTexturePath);
        setPosition({50.f, 50.f});

    }
    void update(float deltaTime) override {
        Character::update(deltaTime);
        handleInput();
    }
    
};