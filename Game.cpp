#include "Game.h"

sf::CircleShape circle(300.0f, 360u);

void Begin(sf::RenderWindow& window) {
    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
    circle.setPosition((sf::Vector2f)window.getSize() / 2.0f);
    circle.setFillColor(sf::Color::Yellow);
}


void Update(float deltaTime) {

}

void Render(sf::RenderWindow& window) {
    window.draw(circle);
}
