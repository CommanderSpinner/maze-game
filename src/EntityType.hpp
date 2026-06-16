#pragma once

#include <string>

enum class entityType {
    BLOCK,
    PLAYER,
    ENEMY,
    ITEM
};

inline std::string typeToString(entityType type) {
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
}