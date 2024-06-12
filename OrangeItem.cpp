//
// Created by kagan on 10.06.2024.
//

#include "OrangeItem.h"
//
// Created by kagan on 8.06.2024.
//

#include "Resources.h"


void OrangeItem::Begin() {
    animation = Animation(1.7f, {
        AnimFrame(1.6f, Resources::textures["orange.png"]),
        AnimFrame(1.5f, Resources::textures["orange1.png"]),
        AnimFrame(1.4f, Resources::textures["orange2.png"]),
        AnimFrame(1.3f, Resources::textures["orange3.png"]),
        AnimFrame(1.2f, Resources::textures["orange4.png"]),
        AnimFrame(1.1f, Resources::textures["orange5.png"]),
        AnimFrame(1.0f, Resources::textures["orange6.png"]),
        AnimFrame(0.9f, Resources::textures["orange7.png"]),
        AnimFrame(0.8f, Resources::textures["orange8.png"]),
        AnimFrame(0.7f, Resources::textures["orange9.png"]),
        AnimFrame(0.6f, Resources::textures["orange10.png"]),
        AnimFrame(0.5f, Resources::textures["orange11.png"]),
        AnimFrame(0.4f, Resources::textures["orange12.png"]),
        AnimFrame(0.3f, Resources::textures["orange13.png"]),
        AnimFrame(0.2f, Resources::textures["orange14.png"]),
        AnimFrame(0.1f, Resources::textures["orange15.png"]),
        AnimFrame(0.0f, Resources::textures["orange16.png"]),
    });
}

void OrangeItem::Update(float deltaTime) {
    animation.Update(deltaTime);
}


void OrangeItem::Render(Renderer &renderer) {
    renderer.Draw(animation.GetTexture(), position, sf::Vector2f(24.0f, 24.0f));
}

sf::FloatRect OrangeItem::GetBounds() const {
    auto size = sf::Vector2f(24.0f, 24.0f);
    return sf::FloatRect(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y);
}

