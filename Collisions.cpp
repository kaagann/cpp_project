//
// Created by kagan on 7.06.2024.
//

#include "Collisions.h"

std::vector<sf::RectangleShape> Collisions::obstacles{};
std::vector<std::vector<sf::Texture*>> Collisions::mapGrid{};
std::vector<std::vector<Object*>> Collisions::objects{};
