#pragma once 

#include "EntityType.hpp"
#include <cstdio>

struct record {
    size_t id;
    float x, y;
    int health;
    entityType type;
};