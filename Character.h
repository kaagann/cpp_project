#pragma once

#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "box2d/b2_body.h"
#include "Physics.h"


class Character : public ContactListener {
public:
    void Begin();
    void Update(float deltaTime);
    void Draw(Renderer& renderer);

    virtual void OnBeginContact() override;
    virtual void OnEndContact() override;

    sf::Vector2f position{};
    float angle{};
private:
    b2Body* body{};
    bool isGrounded = false;

};
