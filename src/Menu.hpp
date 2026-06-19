#pragma once

#include <imgui.h>
#include <imgui-SFML.h>
#include "Database.hpp"
#include "Actions.hpp"

class Menu {
private:
    bool menuOpen = true;
    sf::RenderWindow& window;
    Database& database;

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
public:
    Menu(sf::RenderWindow& w, Database& db) : window(w), database(db) {
        if (!ImGui::SFML::Init(window)) {
            std::fprintf(stderr, "Error with GUI");
        }
    }
    ~Menu() {
        ImGui::SFML::Shutdown();
    }

    void setMenuOpen(bool open) {
        menuOpen = open;
    }

    bool getMenuOpen() {
        return menuOpen;
    }

    MenuAction renderGUI()
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

        MenuAction menuAction;
        
        // maybe switch this later to MenuAction too ----------------
        if (ImGui::Button("Start / Resume Game", ImVec2(buttonSize))) {
            menuOpen = false; // Closes the GUI and resumes game
        }

        if(ImGui::Button("Screen size: 1920, 1080", ImVec2(buttonSize)))
            menuAction = MenuAction::Resize_1920_1080;
        if(ImGui::Button("Screen size: 800, 600", ImVec2(buttonSize)))
            menuAction = MenuAction::Resize_800_600;
        if (ImGui::Button("Save", ImVec2(buttonSize))) 
            menuAction = MenuAction::Save;
        if (ImGui::Button("Load", ImVec2(buttonSize))) 
            menuAction = MenuAction::Load;
        if (ImGui::Button("Exit", ImVec2(buttonSize)))
            menuAction = MenuAction::Exit;

        ImGui::End();
        return menuAction;
    }
};