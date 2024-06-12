#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Map.h"
#include "Renderer.h"

class Character {
public:
    void Begin();
    void Update(float deltaTime);
    void Draw(Renderer& renderer);
    void Reset();
    int GetCherryCount();
    int GetHealth();



    sf::Vector2f position{};
    sf::FloatRect GetBounds();

    float angle{};
    int jumpCount = 0; // Zıplama sayacı
    const int maxJumpCount = 2; // Maksimum zıplama sayısı
    bool isDead = false;
private:
    Animation runAnimation;
    Animation idleAnimation;
    Animation hitAnimation;
    sf::Texture textureToDraw{};

    bool isGrounded = false;
    sf::Vector2f velocity;
    sf::FloatRect rect;
    sf::RectangleShape shape;


    bool facingLeft = false;
    int health; // Karakterin canı
    int cherryCount = 0;

    bool isHit = false; // Hit bayrağı
    float hitTime = 0.0f; // Hit süresi
    const float hitDuration = 0.7f; // Hit animasyon süresi

    bool jumpBuffActive = false;
    float jumpBuffTime = 0.0f;
    const float jumpBuffDuration = 10.0f;
    float jumpVelocity = 200.0f;

};
