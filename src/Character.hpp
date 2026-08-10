#pragma once 

#include "Entity.hpp"
#include "Global.hpp"

class Character : public Entity {
private:
    sf::Vector2f previousPosition;
    Animation idle;
    Animation walk;
    Animation attack;

    AnimationState animationState = AnimationState::Idle;
protected:
    float speed = 185.f;
    void setAnimationState(AnimationState state);
public:
    Character(const sf::Vector2f& pos) : Entity(Global::defaultTexturePath),
          // need to correct later
          idle(0, 0, 4, 32, 32, 0.15f),
          walk(1, 0, 6, 32, 32, 0.10f),
          attack(2, 0, 5, 32, 32, 0.08f, false)
    
    {
        setPosition(pos);

        setAnimation(idle);
    }

    sf::Vector2f getPreviousPosition() {
        return previousPosition;
    }

    virtual void update(float deltaTime) {
        previousPosition = sprite.getPosition();
        sprite.move(movement * deltaTime);
        movement = {0.f, 0.f};
        updateAnimation(deltaTime);
    }
};