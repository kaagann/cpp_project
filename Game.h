#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Renderer.h"

extern Camera camera;

void Begin(sf::RenderWindow& window);
void Update(float deltaTime);
void Render(Renderer& renderer);