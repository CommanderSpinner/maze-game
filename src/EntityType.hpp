#pragma once

#include <string>

enum class entityType {
    BLOCK,
    PLAYER,
    ENEMY,
    ITEM
};

inline std::string entityTypeToString(entityType type) {
    switch(type) {
        case entityType::BLOCK:
            return "BLOCK";
        case entityType::PLAYER:
            return "PLAYER";
        case entityType::ENEMY:
            return "ENEMY";
        case entityType::ITEM:
            return "ITEM";
    }

    return "UNKNOWN";
}

inline entityType stringToEntityType(const std::string& type) {
    if (type == "BLOCK")
        return entityType::BLOCK;
    if (type == "PLAYER")
        return entityType::PLAYER;
    if (type == "ENEMY")
        return entityType::ENEMY;
    if (type == "ITEM")
        return entityType::ITEM;

    throw std::invalid_argument("Unknown entity type: " + type);
}