#pragma once

#include "Entity.hpp"
#include "InputManager.hpp"
#include "Global.hpp"

class Player :  public Entity {
private: 
    InputManager& input;

    float speed = 70.f;

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
    Player(InputManager& im) : Entity(Global::defaultTexture), input(im) {
        setTexture(Global::playerTexturePath);
        setPosition({50.f, 50.f});

    }
    void update(float deltaTime) override {
        // todo: add here code for player movement based on what input manager passes
        handleInput();
        Entity::update(deltaTime);
        movement = {0.f, 0.f};
    }
    
};