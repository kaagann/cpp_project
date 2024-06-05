#pragma once

#include <filesystem>
#include <vector>

#include "Renderer.h"

class Map {
public:
    Map(float cellSize = 16.0f);
    void CreateMap(size_t width, size_t height);
    void Draw(Renderer& renderer);
    sf::Vector2f LoadFromFile(const std::string& fileName); // std::filesystem::path kullanımı
    sf::Vector2f CreateFromImage(const sf::Image& image);

    std::vector<std::vector<int>> grid;
    float cellSize;
};
