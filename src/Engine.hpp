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
        : window(sf::VideoMode({1920, 1080}), "maze game"),
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
        ImVec2 windowPos(window.getSize().x / 2, window.getSize().y / 2);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Always);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove 
                              | ImGuiWindowFlags_NoResize 
                              | ImGuiWindowFlags_NoCollapse 
                              | ImGuiWindowFlags_NoTitleBar;

        ImGui::Begin("Main Menu", &menuOpen, windowFlags);

        styleGUI();
        
        ImGui::Text("Welcome to the Maze Game!");

        ImVec2 buttonSize(180, 40);
        
        if (ImGui::Button("Start / Resume Game", ImVec2(buttonSize))) {
            menuOpen = false; // Closes the GUI and resumes game
        }

        if(ImGui::Button("Screen size: 1920, 1080", ImVec2(buttonSize)))
            window.setSize({1920, 1080});
        if(ImGui::Button("Screen size: 800, 600", ImVec2(buttonSize)))
            window.setSize({800, 600});

        if (ImGui::Button("Exit", ImVec2(buttonSize))) {
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

    void styleGUI() 
    {
        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowPadding = ImVec2(25.0f, 25.0f);   // Breath room inside the menu
        style.ItemSpacing = ImVec2(0.0f, 15.0f);      // Vertical gap between buttons
        
        // --- Borders & Rounding ---
        style.WindowRounding = 12.0f;                 // Smooth corners for the main window
        style.FrameRounding = 8.0f;                   // Smooth corners for the buttons
        style.WindowBorderSize = 2.0f;                // Subtle border around the menu
        style.FrameBorderSize = 0.0f;                 // No harsh borders on buttons

        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.09f, 0.12f, 0.95f);   // Deep, dark blue-grey
        style.Colors[ImGuiCol_Border]   = ImVec4(0.25f, 0.27f, 0.35f, 0.50f);   // Highlight border

        // Buttons (Normal, Hovered, Active)
        style.Colors[ImGuiCol_Button]        = ImVec4(0.65f, 0.15f, 0.15f, 1.00f); // Solid crimson red
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.80f, 0.20f, 0.20f, 1.00f); // Brighter vibrant red on hover
        style.Colors[ImGuiCol_ButtonActive]  = ImVec4(0.50f, 0.10f, 0.10f, 1.00f); // Dark maroon when clicked

        // Typography
        style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.98f, 1.00f);       // Crisp off-white
    }
};