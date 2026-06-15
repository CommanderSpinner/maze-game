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
    Player(InputManager& im) :  Character({50.f, 50.f}), input(im) {
        setTexture(Global::playerTexturePath);
        sprite.setScale({0.8f, 0.8f}); // set scale down for player to fit between tiles
        type = PLAYER;
    }
    
    void update(float deltaTime) override {
        Character::update(deltaTime);
        handleInput();
    }
    
};