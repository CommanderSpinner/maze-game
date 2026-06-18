#pragma once 

#include "EntityType.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Block.hpp"
#include <cstdio>

struct record {
    size_t id;
    float x, y;
    int health;
    std::string type;
};

inline record entityToRecord(Entity entity) {
    record r;

    r.id = entity.getID();
    r.x = entity.getBounds().position.x;
    r.y = entity.getBounds().position.y;
    r.health = entity.getHealth();
    r.type = entityTypeToString(entity.getType());

    return r;
}