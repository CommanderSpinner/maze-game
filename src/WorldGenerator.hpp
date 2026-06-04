#pragma once 

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Block.hpp"
#include <random>
#include "Character.hpp"
#include <memory>

class WorldGenerator {
    std::vector <std::unique_ptr<Entity>>& entity;
    const int TILE_SIZE = 50;

    int width = 150;
    int height = 150;

    std::vector<std::vector<int>> grid;
    std::mt19937 rng{123};

    void generateBlocks() {
        std::uniform_int_distribution<int> wallChance(0, 4);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                bool isWall = (x == 0 || y == 0 ||
                               x == width - 1 || y == height - 1);

                if (!isWall)
                    isWall = (wallChance(rng) == 0); // 20% chance

                if (isWall) {
                    entity.push_back(
                        std::make_unique<Block>(
                            sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE)
                        )
                    );
                }
            }
        }
    }

    void generateEnemys() {
        // entity.push_back(std::make_unique<Character>(sf::Vector2f{100, 100}));
    }

public:
    WorldGenerator(std::vector <std::unique_ptr<Entity>>& e) : entity(e) {
        generateBlocks();
        generateEnemys();
    }

};