#pragma once

#include <SFML/Graphics.hpp>

class Window
{
private:
    sf::RenderWindow window;

public:
    Window()
        : window(sf::VideoMode({800, 600}), "maze game")
    {
    }

    void run()
    {
        while (window.isOpen())
        {
            handleEvents();
            update();
            render();
        }
    }

private:
    void handleEvents()
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }

    void update()
    {
        // game logic 
    }

    void render()
    {
        window.clear(sf::Color::Black);

        // draw stuff here

        window.display();
    }
};