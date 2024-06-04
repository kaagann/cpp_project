#include "Renderer.h"


Renderer::Renderer(sf::RenderTarget& target) : target(target) {

}


void Renderer::Draw(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size) {
    sprite.setTexture(texture);
    sprite.setPosition(position);

    auto sizeX = size.x / texture.getSize().x;
    auto sizeY = size.y / texture.getSize().y;

    sprite.setScale(sf::Vector2f(sizeX, sizeY));

    target.draw(sprite);
}

