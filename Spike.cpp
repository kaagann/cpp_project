//
// Created by kagan on 9.06.2024.
//

#include "Spike.h"

#include "Resources.h"


void Spike::Begin() {

}

void Spike::Render(Renderer &renderer) {
    renderer.Draw(Resources::textures["spike.png"], position, sf::Vector2f(16.0f, 16.0f));
}

void Spike::Update(float deltaTime) {

}

sf::FloatRect Spike::GetBounds() const {
    auto size = sf::Vector2f(2.0f, 2.0f);
    return sf::FloatRect(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y);
}



