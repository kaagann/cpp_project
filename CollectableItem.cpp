//
// Created by kagan on 8.06.2024.
//

#include "CollectableItem.h"

#include "Resources.h"


void CollectableItem::Begin() {
    animation = Animation(1.7f, {
        AnimFrame(1.6f, Resources::textures["cherries.png"]),
        AnimFrame(1.5f, Resources::textures["cherries1.png"]),
        AnimFrame(1.4f, Resources::textures["cherries2.png"]),
        AnimFrame(1.3f, Resources::textures["cherries3.png"]),
        AnimFrame(1.2f, Resources::textures["cherries4.png"]),
        AnimFrame(1.1f, Resources::textures["cherries5.png"]),
        AnimFrame(1.0f, Resources::textures["cherries6.png"]),
        AnimFrame(0.9f, Resources::textures["cherries7.png"]),
        AnimFrame(0.8f, Resources::textures["cherries8.png"]),
        AnimFrame(0.7f, Resources::textures["cherries9.png"]),
        AnimFrame(0.6f, Resources::textures["cherries10.png"]),
        AnimFrame(0.5f, Resources::textures["cherries11.png"]),
        AnimFrame(0.4f, Resources::textures["cherries12.png"]),
        AnimFrame(0.3f, Resources::textures["cherries13.png"]),
        AnimFrame(0.2f, Resources::textures["cherries14.png"]),
        AnimFrame(0.1f, Resources::textures["cherries15.png"]),
        AnimFrame(0.0f, Resources::textures["cherries16.png"]),
    });
}

void CollectableItem::Update(float deltaTime) {
    animation.Update(deltaTime);
}


void CollectableItem::Render(Renderer &renderer) {
    renderer.Draw(animation.GetTexture(), position, sf::Vector2f(24.0f, 24.0f));
}

sf::FloatRect CollectableItem::GetBounds() const {
    auto size = sf::Vector2f(24.0f, 24.0f);
    return sf::FloatRect(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y);
}

