#pragma once 

#include "Entity.hpp"
#include "Global.hpp"

class Character : public Entity {
private:
    sf::Vector2f previousPosition;
protected:
    float speed = 185.f;
public:
    Character(const sf::Vector2f& pos) : Entity(Global::defaultTexturePath) {
        setPosition(pos);
    }

    sf::Vector2f getPreviousPosition() {
        return previousPosition;
    }

    virtual void update(float deltaTime) {
        previousPosition = sprite.getPosition();
        sprite.move(movement * deltaTime);
        movement = {0.f, 0.f};
    }
};