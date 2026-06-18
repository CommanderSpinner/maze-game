#pragma once

#include "InputManager.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>
#include "WorldGenerator.hpp"
#include "Collision.hpp"
#include "Menu.hpp"
#include "Database.hpp"

class Engine {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    InputManager im;
    std::vector <std::unique_ptr<Entity>> entitys;
    sf::View camera;
    Menu menu;
    Database database;

public:
    Engine()
        : window(sf::VideoMode({1920, 1080}), "maze game"),
          camera({640.f, 360.f}, {1280.f, 720.f}),
          menu(window, database)
    {   
        entitys.push_back(std::make_unique<Player>(im));
        WorldGenerator g(entitys);
    }

    ~Engine() {}

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
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
                window.close();

            // Toggle menu with Escape key
            if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    menu.setMenuOpen(!menu.getMenuOpen());
                }
            }
            // Only pass inputs to the game if the menu isn't open
            if (!menu.getMenuOpen()) {
                im.processEvent(*event);
            }
        }
    }

    void update()
    {   
        sf::Time deltaTime = clock.restart();

        // If deltaTime is 0 give it a tiny positive value to not crash
        if (deltaTime.asSeconds() <= 0.0f) {
            deltaTime = sf::seconds(1.f / 60.f); // Default to a 60 FPS frame time
        }

        ImGui::SFML::Update(window, deltaTime);

        if (menu.getMenuOpen()) {
            menu.renderGUI();
        } else {

            for (auto& e : entitys) {
                float dtSeconds = deltaTime.asSeconds();
                e->update(dtSeconds);
            }

            Collision collision(entitys);

            // Center camera on player
            camera.setCenter(entitys[0]->getPosition());
        }
        window.setView(camera);
    }

    void render()
    {
        window.clear(sf::Color::Black);

        for (auto& e : entitys) {
            e->draw(window);
        }

        ImGui::SFML::Render(window);

        window.display();
    }
};