#pragma once 

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Block.hpp"

class WorldGenerator {
    std::vector <std::unique_ptr<Entity>>& entity;
    const int TILE_SIZE = 50;

    int width = 150;
    int height = 150;

    std::vector<std::vector<int>> grid;

    void generate()
    {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                // border walls
                bool isWall = (x == 0 || y == 0 || x == width - 1 || y == height - 1);

                // random internal walls (temporary generator)
                if (!isWall)
                    isWall = (rand() % 5 == 0);

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

public:
    WorldGenerator(std::vector <std::unique_ptr<Entity>>& e) : entity(e) {
        generate();
    }

};