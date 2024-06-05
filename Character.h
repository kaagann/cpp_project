#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "box2d/b2_body.h"

class Character {
public:
    void Begin();
    void Update(float deltaTime);
    void Draw(Renderer& renderer);
    sf::Vector2f position{};
    float angle{};
private:
    b2Body* body;
};
