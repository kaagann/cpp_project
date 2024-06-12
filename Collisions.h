#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "Object.h"



class Collisions {
public:
    static std::vector<sf::RectangleShape> obstacles;
    static std::vector<std::vector<sf::Texture*>> mapGrid;
    static std::vector<std::vector<Object*>> objects;
};



