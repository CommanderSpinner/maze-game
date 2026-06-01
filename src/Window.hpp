#pragma once

#include "InputManager.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>

class Window {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    InputManager im;
    std::vector <std::unique_ptr<Entity>> entitys;

public:
    Window()
        : window(sf::VideoMode({800, 600}), "maze game")
    {
        entitys.push_back(std::make_unique<Player>(im));
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

            im.processEvent(*event);
        }
    }

    void update()
    {
        float deltaTime = clock.restart().asSeconds();

        for (auto& e : entitys) {
            e->update(deltaTime);
        }

    }

    void render()
    {
        window.clear(sf::Color::Black);

        for (auto& e : entitys) {
            e->draw(window);
        }

        window.display();
    }
};