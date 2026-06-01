#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Global.hpp"

class Block : public Entity {
    Block(sf::Vector2 position) : Entity(Global::defaultTexture) {
        setTexture(Global::blockTexture);
        sprite.setPosition(position);
    }
};