#pragma once

#include <SFML/Graphics.hpp>

class InputManager {
    public:
    void processEvent(const sf::Event& event) {
         // Key pressed
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::A)
                moveLeft = true;

            if (keyPressed->code == sf::Keyboard::Key::D)
                moveRight = true;

            if (keyPressed->code == sf::Keyboard::Key::W)
                moveUp = true;

            if (keyPressed->code == sf::Keyboard::Key::S)
                moveDown = true;
        }

        // Key released
        if (const auto* keyReleased = event.getIf<sf::Event::KeyReleased>())
        {
            if (keyReleased->code == sf::Keyboard::Key::A)
                moveLeft = false;

            if (keyReleased->code == sf::Keyboard::Key::D)
                moveRight = false;

            if (keyReleased->code == sf::Keyboard::Key::W)
                moveUp = false;

            if (keyReleased->code == sf::Keyboard::Key::S)
                moveDown = false;
        }
    }

    bool isMovingLeft() const { return moveLeft; }
    bool isMovingRight() const { return moveRight; }
    bool isMovingUp() const { return moveUp; }
    bool isMovingDown() const { return moveDown; }

private:
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;
};