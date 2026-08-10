#pragma once

#include <SFML/Graphics.hpp>
#include "EntityType.hpp"
#include "Animation.hpp"

class Database;

class Entity {
    static inline int count = 0;
    int health = 100;
protected:
    entityType type;
    size_t id;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f movement;

    Animation* currentAnimation = nullptr;

    void setAnimation(Animation& animation) {
        if (currentAnimation == &animation)
            return;

        currentAnimation = &animation;
        currentAnimation->reset();
    }

    void updateAnimation(float deltaTime) {
        if (currentAnimation) {
            currentAnimation->update(deltaTime);
            currentAnimation->applyToSprite(sprite);
        }
    }

public:

    virtual ~Entity() = default;
    Entity(std::string texturePath) :  sprite(texture), movement({0.f, 0.f}) {
        id = count;
        count++;

        setTexture(texturePath);
    }

    static size_t getCount() {
        return count;
    }

    size_t getID() {
        return id;
    }

    void setID(size_t id) {
        this->id = id;
    }

    entityType getType() {
        return type;
    }

    int getHealth() {
        return health;
    }

    void setHealth(int health) {
        this->health = health;
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
        updateAnimation(deltaTime);
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