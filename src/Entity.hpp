#pragma once

#include <SFML/Graphics.hpp>


class Entity {
protected:
    sf::Sprite sprite;
    sf::Vector2f velocity;
public:

    virtual ~Entity() = default;
    Entity() : velocity({0.f, 0.f}) {}

    virtual void update(float deltaTime) {}
    
    virtual void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void setPosition(const sf::Vector2f& pos) {
        sprite.setPosition(pos);
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    void setTexture(const sf::Texture& texture) {
        sprite.setTexture(texture);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};