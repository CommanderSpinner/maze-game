#pragma once

#include <SFML/Graphics.hpp>


class Entity {
public:
    int cordsX = 0, cordsY = 0;
    sf::RectangleShape box({50.f, 50.f});

    virtual ~Entity() = default;

    virtual void update(float dt) {}
    virtual void draw(sf::RenderWindow& window) {}
};