//
// Created by kagan on 12.06.2024.
//

#include "EndPoint.h"
//
// Created by kagan on 9.06.2024.
//

#include "Resources.h"


void EndPoint::Begin() {

}

void EndPoint::Render(Renderer &renderer) {
    renderer.Draw(Resources::textures["end.png"], position, sf::Vector2f(16.0f, 16.0f));
}

void EndPoint::Update(float deltaTime) {

}

sf::FloatRect EndPoint::GetBounds() const {
    auto size = sf::Vector2f(16.0f, 16.0f);
    return sf::FloatRect(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y);
}





