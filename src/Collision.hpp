#pragma once

#include "Character.hpp"
#include "Player.hpp"

class Collision {
    std::vector <std::unique_ptr<Entity>>& entity;
    std::vector<Character*> characters;

    void handleCollision() {
        for (size_t i = 0; i < characters.size(); i++) {
            for (size_t j = 0; j < entity.size(); j++) {

                sf::FloatRect a = characters[i]->getSprite().getGlobalBounds();
                sf::FloatRect b = entity[j]->getSprite().getGlobalBounds();
                
                if (a.findIntersection(b)) {
                }
            }
        }
    }

    void extractMovingEntitys() {
        for (const auto& e : entity) {
            if (auto* c = dynamic_cast<Character*>(e.get())) {
                characters.push_back(c);
            }
        }
    }
public:
    Collision(std::vector <std::unique_ptr<Entity>>& e) : entity(e) {
        extractMovingEntitys();
        handleCollision();
    }

    
};