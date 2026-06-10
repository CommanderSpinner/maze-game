#pragma once

#include "InputManager.hpp"
#include "Player.hpp"
#include <vector>
#include <memory>
#include "WorldGenerator.hpp"
#include "Collision.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

class Engine {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    InputManager im;
    std::vector <std::unique_ptr<Entity>> entitys;
    sf::View camera;
    bool menuOpen = true;

public:
    Engine()
        : window(sf::VideoMode({800, 600}), "maze game"),
        camera({640.f, 360.f}, {1280.f, 720.f})
    {   
        if (!ImGui::SFML::Init(window)) {
            std::fprintf(stderr, "Error with GUI");
        }

        entitys.push_back(std::make_unique<Player>(im));
        WorldGenerator g(entitys);
    }

    ~Engine() 
    {
        ImGui::SFML::Shutdown();
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
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
                window.close();

            // Toggle menu with Escape key
            if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    menuOpen = !menuOpen;
                }
            }
            // Only pass inputs to the game if the menu isn't open
            if (!menuOpen) {
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

        if (menuOpen) {
            renderGUI();
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

    void renderGUI()
    {
        // Center the window on screen nicely
        ImGui::SetNextWindowPos(ImVec2(300, 200), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);

        ImGui::Begin("Main Menu", &menuOpen);
        
        ImGui::Text("Welcome to the Maze Game!");
        
        if (ImGui::Button("Start / Resume Game", ImVec2(180, 40))) {
            menuOpen = false; // Closes the GUI and resumes game
        }

        if (ImGui::Button("Exit", ImVec2(180, 40))) {
            window.close();
        }

        ImGui::End();
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