//
// Created by kagan on 4.06.2024.
//

#include "Map.h"
#include "Resources.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <filesystem>

#include "Physics.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "fmt/args.h"

Map::Map(float cellSize) : cellSize(cellSize) , grid() {

}

void Map::CreateMap(size_t width, size_t height) {
    grid = std::vector(width, std::vector(height, 0));

    bool last = 0;
    for (auto& column : grid)
    {
        for (auto& cell : column)
        {
            last = !last;
            if (last)
                cell = last;
        }
        if (width % 2 == 0)
            last = !last;
    }
}

void Map::Draw(Renderer& renderer) {
    int y = 0;
    for (const auto& row : grid) { // grid'in sütunları yerine satırlarını kullan
        int x = 0;
        for (const auto& cell : row) { // sütun hücreleri yerine satır hücrelerini kullan
            if (cell) {
                renderer.Draw(Resources::textures["terrain.png"], sf::Vector2f(cellSize * x + cellSize / 2.0f,
                    cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize * 2 , cellSize * 2), sf::IntRect(16,16,16,16));
            }
            x++;
        }
        y++;
    }
}

sf::Vector2f Map::LoadFromFile(const std::string& fileName) {
    namespace fs = std::filesystem;

    auto path = fs::path(fileName);
    std::cout << "Loading map from: " << path << std::endl;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + fileName);
    }

    size_t width = 0;
    size_t height = 0;
    std::string line;
    while (std::getline(file, line)) {
        width = std::max(width, line.size());
        height++;
    }

    grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));

    file.clear();
    file.seekg(0);

    size_t y = 0;

    sf::Vector2f characterPosition;

    while (std::getline(file, line)) {
        for (size_t x = 0; x < line.size(); ++x) {
            char c = line[x];
            if (c == '0' || c == ' ') {
                grid[y][x] = 0;
            } else if (c == '1') {
                grid[y][x] = 1;
                b2BodyDef body_def{};
                body_def.position.Set(cellSize * x + cellSize / 2.0f,
                    cellSize * y + cellSize / 2.0f);
                b2Body* body = Physics::world.CreateBody(&body_def);
                b2PolygonShape shape{};
                shape.SetAsBox(cellSize / 2.0f, cellSize / 2.0f);
                body->CreateFixture(&shape, 0);
            } else if (c == 'x') {
                characterPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f,
                    cellSize * y + cellSize / 2.0f);
            } else {
                throw std::runtime_error("Invalid character in map file: " + std::string(1, c));
            }
        }
        y++;
    }

    return characterPosition;
}

