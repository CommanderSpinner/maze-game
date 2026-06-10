#pragma once

#include "InputManager.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>
#include "WorldGenerator.hpp"
#include "Collision.hpp"

class Engine {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    InputManager im;
    std::vector <std::unique_ptr<Entity>> entitys;
    sf::View camera;

public:
    Engine()
        : window(sf::VideoMode({800, 600}), "maze game"),
        camera({640.f, 360.f}, {1280.f, 720.f})
    {
        entitys.push_back(std::make_unique<Player>(im));
        WorldGenerator g(entitys);
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

        Collision collision(entitys);

        // Center camera on player
        camera.setCenter(entitys[0]->getPosition());

        // Apply camera
        window.setView(camera);

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