#pragma once

#include "Character.hpp"

class Enemy : public Character {
private:
    // check where to move and go other directions if player is spotted or a wall is hit
    void checkMovement() {

    }
public:
    Enemy(const sf::Vector2f& pos) : Character(pos) {
        setTexture(Global::enemyTexturePath);
    }

    void update(float deltaTime) {
        Character::update(deltaTime);
        checkMovement();
        // TODO: add health reduction or something like that when enemy hits a player
    
    }
};