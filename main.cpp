#include <SFML/Graphics.hpp>

#include "Game.h"

auto main() -> int {
    auto window = sf::RenderWindow(
               sf::VideoMode({1200, 900}), "Crazy Frog",
               sf::Style::Default, sf::ContextSettings(0, 0, 8)
       );
    sf::Clock deltaClock;


    Begin(window);
    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();


        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Update(deltaTime);
        window.clear();
        Render(window);
        window.display();

    }


}
