#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Global.hpp"

class Block : public Entity {
public:
    Block(sf::Vector2f position) : Entity(Global::defaultTexturePath) {
        setTexture(Global::blockTexturePath);
        sprite.setPosition(position);
        sprite.setScale(sf::Vector2f(1.f, 1.f));
        type = BLOCK;
    }
};