#include "Game.h"

sf::Texture texture;

void Begin(sf::RenderWindow& window) {
    if (!texture.loadFromFile("textures/brick.png"))
        exit(-1);
}


void Update(float deltaTime) {

}

void Render(Renderer &renderer) {
    renderer.Draw(texture, sf::Vector2f(), sf::Vector2f(2,2));
}
