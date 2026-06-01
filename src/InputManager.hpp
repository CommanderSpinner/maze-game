#pragma once

#include <SFML/Graphics.hpp>

class InputeManager {
    public:
    void processEvent(const sf::Event& event) {
         // Key pressed
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::A)
                m_moveLeft = true;

            if (keyPressed->code == sf::Keyboard::Key::D)
                m_moveRight = true;
        }

        // Key released
        if (const auto* keyReleased = event.getIf<sf::Event::KeyReleased>())
        {
            if (keyReleased->code == sf::Keyboard::Key::A)
                m_moveLeft = false;

            if (keyReleased->code == sf::Keyboard::Key::D)
                m_moveRight = false;
        }
    }

    bool moveLeft() const { return m_moveLeft; }
    bool moveRight() const { return m_moveRight; }

private:
    bool m_moveLeft = false;
    bool m_moveRight = false;
};