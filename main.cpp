#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Game.h"
#include "Renderer.h"

auto main() -> int {
    auto window = sf::RenderWindow(
               sf::VideoMode({1280, 720}), "Crazy Frog",
               sf::Style::Default, sf::ContextSettings(0, 0, 8)
    );
    sf::Clock deltaClock;
    Renderer renderer(window);

    sf::Texture texture;


    window.setFramerateLimit(60);
    Begin(window);
    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();


        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                paused = !paused;
        }


        Update(deltaTime);
        window.clear(sf::Color::Blue);

        window.setView(camera.GetView(window.getSize()));
        Render(renderer);


        window.setView(camera.GetUIView());
        RenderUI(renderer);
        window.display();

    }


}
