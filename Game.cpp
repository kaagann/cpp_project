#include "Game.h"
#include "Resources.h"
#include <filesystem>

#include "Character.h"
#include "Collisions.h"
#include "Map.h"
#include "Object.h"
#include "fmt/ostream.h"
#include "SFML/Audio.hpp"



auto cellSize = 16.0f;

Map map(cellSize);
Camera camera(320.0f);
Character character{};

bool paused{};


sf::Font font{};
sf::Text coinsText("Coins", font);
sf::Text healthText("Health", font);
sf::Text restartText("Press SPACE to start the game", font);


sf::RectangleShape backgroundShape(sf::Vector2f(1.0f, 1.0f));

void Restart() {
    for (auto& column : Collisions::objects) {
        for (auto& object : column) {
            if (object != nullptr) {
                delete object;
                object = nullptr;
            }
        }
    }

    Collisions::objects.clear();
    character.Reset();

    sf::Image image;
    image.loadFromFile("../assets/textures/map.png");
    character.position = map.CreateFromImage(image);

    character.Begin();

    auto x = 0;
    for (const auto& column : Collisions::objects) {
        int y = 0;
        for (const auto& object : column) {
            if (object != nullptr) {
                object->Begin();
            }
            y++;
        }
        x++;
    }
    paused = false;
}


void Begin(sf::RenderWindow& window) {
    for (auto& file: std::filesystem::directory_iterator("../assets/textures/")) {
        if (file.is_regular_file() && file.path().extension() == ".png") {
            fmt::println("{}", file.path().string());
            Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
        }
    }


    for (auto& file : std::filesystem::directory_iterator("./assets/sounds/"))
    {
        if (file.is_regular_file() && (file.path().extension() == ".mp3" || file.path().extension() == ".wav"))
        {
            Resources::sounds[file.path().filename().string()].loadFromFile(
                file.path().string());
        }
    }


    //map.CreateMap(10, 10);
    //character.position = map.LoadFromFile("../map.txt");
    sf::Image image;
    image.loadFromFile("../assets/textures/map.png");
    character.position = map.CreateFromImage(image);

    character.Begin();

    auto x = 0;
    for (const auto& column : Collisions::objects) {
        int y = 0;
        for (const auto& object : column) {
            if (object != nullptr) {
                object->Begin();
            }
            y++;
        }
        x++;
    }

    font.loadFromFile("../assets/pixelfont.ttf");

    coinsText.setFillColor(sf::Color::White);
    coinsText.setOutlineColor(sf::Color::Black);
    coinsText.setOutlineThickness(1.0f);
    coinsText.setScale(0.05f, 0.05f);

    healthText.setFillColor(sf::Color::White);
    healthText.setOutlineColor(sf::Color::Black);
    healthText.setOutlineThickness(1.0f);
    healthText.setScale(0.05f, 0.05f);

    restartText.setFillColor(sf::Color::White);
    restartText.setOutlineColor(sf::Color::Black);
    restartText.setOutlineThickness(1.0f);
    restartText.setScale(0.1f, 0.1f);
    restartText.setPosition(-restartText.getLocalBounds().width / 2, -restartText.getLocalBounds().height / 2);

    backgroundShape.setFillColor(sf::Color(0,0,0,150));
    backgroundShape.setOrigin(backgroundShape.getSize().x / 2, backgroundShape.getSize().y / 2);


}


void Update(float deltaTime) {

    if (character.isDead && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Restart();


    if (character.isDead)
        paused = true;

    if (paused)
        return;


    character.Update(deltaTime);
    camera.position = character.position;




    auto x = 0;
    for (const auto& column : Collisions::objects) {
        int y = 0;
        for (const auto& object : column) {
            if (object != nullptr) {
                object->Update(deltaTime);
            }
            y++;
        }
        x++;
    }




}

void Render(Renderer &renderer) {
    map.Draw(renderer);
    character.Draw(renderer);

    auto x = 0;
    for (const auto& column : Collisions::objects) {
        int y = 0;
        for (const auto& object : column) {
            if (object != nullptr) {
                object->Render(renderer);
            }
            y++;
        }
        x++;
    }
}

void RenderUI(Renderer &renderer) {
    auto cherryCount = character.GetCherryCount();

    if (cherryCount > 0) {
        renderer.target.draw(coinsText);
        coinsText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 4.0f));
        coinsText.setString("Collected Cherry: " + std::to_string(character.GetCherryCount()));
    }

    renderer.target.draw(healthText);
    healthText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(2.0f, 2.0f));
    healthText.setString("Health: " + std::to_string(character.GetHealth()));


    if (paused) {
        backgroundShape.setScale(camera.GetViewSize());
        renderer.target.draw(backgroundShape);

        restartText.setPosition(-camera.GetViewSize() / 2.0f + sf::Vector2f(30.0f, 23.0f));

        renderer.target.draw(restartText);
    }

}


