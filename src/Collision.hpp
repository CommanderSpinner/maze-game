#pragma once

#include "Character.hpp"

class Collision {
    std::vector <std::unique_ptr<Entity>>& entitys;

    void handleCollision() {
        
    }
public:
    Collision(std::vector <std::unique_ptr<Entity>>& e) : entitys(e) {
        handleCollision();
    }

    
};