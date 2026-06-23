#pragma once 

#include "EntityType.hpp"
#include "Entity.hpp"
#include <cstdio>
#include <memory>

struct record {
    size_t id;
    float x, y;
    int health;
    std::string type;
};

inline record entityToRecord(Entity& entity) {
    record r;

    r.id = entity.getID();
    r.x = entity.getBounds().position.x;
    r.y = entity.getBounds().position.y;
    r.health = entity.getHealth();
    r.type = entityTypeToString(entity.getType());

    return r;
}

inline std::unique_ptr<Entity> recordToEntity(record r, InputManager& im) {
    std::unique_ptr<Entity> e;

    // creating corresponding object type to entityType
    switch(stringToEntityType(r.type)) {
        case entityType::BLOCK:
            e = std::make_unique<Block>(sf::Vector2f{0.f, 0.f});
            break;
        case entityType::PLAYER:
            e = std::make_unique<Player>(im);
        case entityType::ENEMY:
            e = std::make_unique<Enemy>(sf::Vector2f{0.f, 0.f});
            break;
        case entityType::ITEM:
            break;
    }

    // setting other attributes

    e->setID(r.id);
    e->setHealth(r.health);
    e->setPosition(sf::Vector2f{r.x, r.y});

    return e;
}