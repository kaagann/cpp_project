//
// Created by kagan on 4.06.2024.
//

#include "Map.h"
#include "Resources.h"
#include "Collisions.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <filesystem>

#include "CollectableItem.h"
#include "OrangeItem.h"
#include "RockHead.h"
#include "Spike.h"
#include "fmt/args.h"

Map::Map(float cellSize) : cellSize(cellSize) , grid() {

}

bool isColor(sf::Color color, int r, int g, int b) {
    return color.r == r && color.g == g && color.b == b;
}




void Map::Draw(Renderer& renderer)
{
    int x = 0;
    for (const auto& column : grid)
    {
        int y = 0;
        for (const auto& cell : column)
        {
            if (cell)
            {
                renderer.Draw(*cell, sf::Vector2f(cellSize * x + cellSize / 2.0f,
                    cellSize * y + cellSize / 2.0f), sf::Vector2f(cellSize, cellSize));
            }
            y++;
        }
        x++;
    }

    for (const auto& obstacle : Collisions::obstacles) {
        renderer.Draw(Resources::textures["brick.png"], obstacle.getPosition(), obstacle.getSize());
    }
}

sf::Vector2f Map::CreateFromImage(const sf::Image& image) {
    grid.clear();

    grid = std::vector(image.getSize().x, std::vector(image.getSize().y,
        (sf::Texture*)nullptr));
    sf::Vector2f characterPosition;
    auto objectGrid = std::vector<std::vector<Object*>>(image.getSize().x, std::vector<Object*>(image.getSize().y, nullptr));

    Collisions::obstacles.clear();
    Collisions::objects.clear();

    for (size_t x = 0; x < grid.size(); x++) {
        for (size_t y = 0; y < grid[x].size(); y++) {
            sf::Color color = image.getPixel(x,y);
            if (color == sf::Color::Black) {
                grid[x][y] = &Resources::textures["terrain1.png"];
            } else if (color == sf::Color::Yellow) {
                grid[x][y] = &Resources::textures["terrain2.png"];
            } else if (color == sf::Color::Blue) {
                grid[x][y] = &Resources::textures["terrain3.png"];
            } else if (isColor(color, 33, 33, 33)) {
                grid[x][y] = &Resources::textures["terrain4.png"];
            } else if (isColor(color, 0, 255, 132)) {
                grid[x][y] = &Resources::textures["terrain5.png"];
            } else if (isColor(color, 0, 255, 12)) {
                grid[x][y] = &Resources::textures["terrain6.png"];
            } else if (isColor(color, 88, 88, 164)) {
                grid[x][y] = &Resources::textures["walltop.png"];
            } else if (isColor(color, 39, 39, 167)) {
                grid[x][y] = &Resources::textures["wallbottom.png"];
            } else if (isColor(color, 88, 164, 143)) {
                grid[x][y] = &Resources::textures["wallright1.png"];
            } else if (isColor(color, 118, 131, 118)) {
                grid[x][y] = &Resources::textures["wallright2.png"];
            } else if (isColor(color, 88, 164, 90)) {
                grid[x][y] = &Resources::textures["wallright3.png"];
            } else if (isColor(color, 47, 221, 53)) {
                grid[x][y] = &Resources::textures["wallleft1.png"];
            } else if (isColor(color, 128, 128, 128)) {
                grid[x][y] = &Resources::textures["wallleft2.png"];
            } else if (isColor(color, 33, 162, 37)) {
                grid[x][y] = &Resources::textures["wallleft3.png"];
            } else if (isColor(color, 36, 105, 69)) {
                grid[x][y] = &Resources::textures["step2.png"];
            } else if (isColor(color, 45, 129, 85)) {
                grid[x][y] = &Resources::textures["step3.png"];
            } else if (isColor(color, 53, 158, 103)) {
                grid[x][y] = &Resources::textures["step1.png"];
            } else if (isColor(color, 132, 99, 132)) {
                grid[x][y] = &Resources::textures["brick1.png"];
            } else if (isColor(color, 87, 64, 87)) {
                grid[x][y] = &Resources::textures["brick2.png"];
            } else if (isColor(color, 56, 41, 56)) {
                grid[x][y] = &Resources::textures["brick3.png"];
            } else if (isColor(color, 255, 0, 255)) {
                Object* item = new CollectableItem();
                item->position = sf::Vector2f(cellSize * x + cellSize / 2.0f,
                    cellSize * y + cellSize / 2.0f);
                objectGrid[x][y] = item;
            } else if (isColor(color, 195, 200, 117)) {
                Object* item = new RockHead();
                item->position = sf::Vector2f(cellSize * x + cellSize / 2.0f,
                    cellSize * y + cellSize / 2.0f);
                objectGrid[x][y] = item;
            } else if (isColor(color, 174, 83, 38)) {
                Object* item = new Spike();
                item->position = sf::Vector2f(cellSize * x + cellSize / 2.0f,
                    cellSize * y + cellSize / 2.0f);
                objectGrid[x][y] = item;
            } else if (isColor(color, 226, 116, 62)) {
                Object* item = new OrangeItem();
                item->position = sf::Vector2f(cellSize * x + cellSize / 2.0f,
                    cellSize * y + cellSize / 2.0f);
                objectGrid[x][y] = item;
            } else if (color == sf::Color::Red)
                characterPosition = sf::Vector2f(cellSize * x + cellSize / 2.0f,
                    cellSize * y + cellSize / 2.0f);
        }
    }

    Collisions::objects = objectGrid;
    Collisions::mapGrid = grid;
    return characterPosition;
}



