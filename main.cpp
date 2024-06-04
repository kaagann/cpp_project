#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Game.h"
#include "Renderer.h"

auto main() -> int {
    auto window = sf::RenderWindow(
               sf::VideoMode({1200, 900}), "Crazy Frog",
               sf::Style::Default, sf::ContextSettings(0, 0, 8)
       );
    sf::Clock deltaClock;
    Camera camera;
    Renderer renderer(window);

    sf::Texture texture;





    Begin(window);
    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();


        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.setView(camera.GetView(window.getSize()));
        Update(deltaTime);
        window.clear();
        Render(renderer);
        window.display();

    }


}
