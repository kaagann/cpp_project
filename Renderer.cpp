#include "Renderer.h"


Renderer::Renderer(sf::RenderTarget& target) : target(target) {

}


void Renderer::Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, float angle) {
    auto sizeX = size.x / texture.getSize().x;
    auto sizeY = size.y / texture.getSize().y;
    auto origin = (sf::Vector2f) texture.getSize() / 2.0f;

    sprite.setTexture(texture, true);
    sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);

    sprite.setRotation(angle);
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(size.x / texture.getSize().x,
        size.y / texture.getSize().y));
    target.draw(sprite);
}


