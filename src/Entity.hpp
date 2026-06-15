#pragma once

#include <SFML/Graphics.hpp>
#include "Database.hpp"

enum entityType {
    BLOCK,
    PLAYER,
    ENEMY,
    ITEM
};

class Entity {
    static inline int count = 0;
protected:
    entityType type;
    int id;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f movement;
public:

    virtual ~Entity() = default;
    Entity(std::string texturePath) :  sprite(texture), movement({0.f, 0.f}) {
        id = count;
        count++;

        setTexture(texturePath);
    }

    sf::Sprite& getSprite() {
        return sprite;
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

    virtual void update(float deltaTime) {
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