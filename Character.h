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
    void ResetJumpCount(); // New function to reset jump count

    sf::Vector2f position{};
    sf::FloatRect GetBounds();

    float angle{};
    bool isDead = false;

private:
    Animation runAnimation;
    Animation idleAnimation;
    Animation hitAnimation;
    Animation dJumpAnimation;
    sf::Texture textureToDraw{};

    bool isGrounded = false;
    sf::Vector2f velocity;
    sf::FloatRect rect;
    sf::RectangleShape shape;


    bool facingLeft = false;
    int health; // Karakterin canı
    int defaultHealth = 10;
    int cherryCount = 0;

    bool isHit = false; // Hit bayrağı
    float hitTime = 0.0f; // Hit süresi
    const float hitDuration = 0.7f; // Hit animasyon süresi

    bool jumpBuffActive = false;
    float jumpBuffTime = 0.0f;
    const float jumpBuffDuration = 10.0f;
    float jumpVelocity = 200.0f;

    int jumpCount = 0; // Zıplama sayacı
    const int maxJumpCount = 2; // Maksimum zıplama sayısı
    bool jumpPressed = false; // Zıplama tuşunun önceki durumu

};
