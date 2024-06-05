#include "Game.h"
#include "Resources.h"
#include <filesystem>

#include "Character.h"
#include "Map.h"
#include "Physics.h"
#include "fmt/ostream.h"


Map map(16.0f);
Camera camera(320.0f);
Character character;

void Begin(sf::RenderWindow& window) {
    for (auto& file: std::filesystem::directory_iterator("../textures/")) {
        if (file.is_regular_file() && file.path().extension() == ".png") {
            fmt::println("{}", file.path().string());
            Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
        }
    }

    Physics::Init();
    //map.CreateMap(10, 10);
    //character.position = map.LoadFromFile("../map.txt");
    sf::Image image;
    image.loadFromFile("../textures/map.png");
    character.position = map.CreateFromImage(image);

    character.Begin();
}


void Update(float deltaTime) {
    Physics::Update(deltaTime);
    character.Update(deltaTime);
    camera.position = character.position;

}

void Render(Renderer &renderer) {
    map.Draw(renderer);
    character.Draw(renderer);

    Physics::DebugDraw(renderer);
}
