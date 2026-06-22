#pragma once

#include "InputManager.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>
#include "WorldGenerator.hpp"
#include "Collision.hpp"
#include "Menu.hpp"
#include "Database.hpp"
#include "Actions.hpp"
#include "utils.hpp"

class Engine {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    InputManager im;
    std::vector <std::unique_ptr<Entity>> entitys;
    sf::View camera;
    Menu menu;
    MenuAction menuAction = MenuAction::None;

public:
    Engine()
        : window(sf::VideoMode({1920, 1080}), "maze game", sf::Style::Default),
          camera({640.f, 360.f}, {1280.f, 720.f}),
          menu(window)
    {   
        entitys.push_back(std::make_unique<Player>(im));
        WorldGenerator g(entitys);
        DBG_PRINTF("ammount of Entitys: %i\n", Entity::getCount());
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

            // Handle window resizing
            if (auto* resized = event->getIf<sf::Event::Resized>())
            {
                float width = static_cast<float>(resized->size.x);
                float height = static_cast<float>(resized->size.y);

                sf::Vector2f center = camera.getCenter();

                camera.setSize({
                    1280.f,
                    1280.f * height / width
                });

                camera.setCenter(center);
            }

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
            menuAction = menu.renderGUI();
            handleGUI();
        } else {

            for (auto& e : entitys) {
                float dtSeconds = deltaTime.asSeconds();
                e->update(dtSeconds);
            }

            Collision collision(entitys);

            // Center camera on player
            camera.setCenter(entitys[0]->getPosition());
        }
    }

    void render()
    {
        window.clear(sf::Color::Black);

        window.setView(camera);

        for (auto& e : entitys) {
            e->draw(window);
        }

        ImGui::SFML::Render(window);

        window.display();
    }

    void handleGUI() {
        switch (menuAction) {
            case MenuAction::Save:
                save();
                menuAction = MenuAction::None;
                break;
            case MenuAction::Load:
                load();
                menuAction = MenuAction::None;
                break;
            case MenuAction::Resize_1920_1080: 
                window.setSize({1920, 1080});
                menuAction = MenuAction::None;
                break;
            case MenuAction::Resize_800_600:
                window.setSize({800, 600});
                menuAction = MenuAction::None;
                break;
            case MenuAction::Exit:
                window.close();
                menuAction = MenuAction::None;
                break;
            case MenuAction::None:
                break;
        }
    }

    void save() {
        Database db;
        std::vector<record> r;
        r.reserve(entitys.size());

        for (auto& e : entitys) {
            r.push_back(entityToRecord(*e));
            DBG_PRINTF("inserting: %i\n", e->getID());
        }

        db.insert(r);
    }

    void load() {

    }
};