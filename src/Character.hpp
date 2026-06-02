#pragma once 

#include "Entity.hpp"
#include "Global.hpp"

class Character : public Entity {
protected:
    float speed = 185.f;
public:
    Character() : Entity(Global::defaultTexture) {

    }

    virtual void update(float deltaTime) {
        sprite.move(movement * deltaTime);
        movement = {0.f, 0.f};
    }
};