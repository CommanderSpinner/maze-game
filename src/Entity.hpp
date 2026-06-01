#pragma once

#include <SFML/Graphics.hpp>


class Entity {
    static inline int count = 0;
protected:
    int id;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
public:

    virtual ~Entity() = default;
    Entity(std::string texturePath) :  sprite(texture), velocity({0.f, 0.f}) {
        id = count;
        count++;

        setTexture(texturePath);
    }

    virtual void update(float deltaTime) {
        sprite.move(velocity * deltaTime);
    }
    
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    void setPosition(const sf::Vector2f& pos) {
        sprite.setPosition(pos);
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    void setTexture(std::string texturePath) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture from path: " + texturePath);
        }
        sprite.setTexture(texture, true);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};