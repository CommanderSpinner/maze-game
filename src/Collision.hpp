#pragma once

#include "Character.hpp"
#include "Player.hpp"

class Collision {
    std::vector <std::unique_ptr<Entity>>& entity;
    std::vector<Character*> characters;

    void handleCollision() {
        for (size_t i = 0; i < characters.size(); i++) {
            for (size_t j = 0; j < entity.size(); j++) {

                sf::FloatRect characterRect = characters[i]->getSprite().getGlobalBounds();
                sf::FloatRect entityRect = entity[j]->getSprite().getGlobalBounds();
                
                // checking for self intersect
                if (characters[i] == entity[j].get())
                    continue;

                if (characterRect.findIntersection(entityRect)) {
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