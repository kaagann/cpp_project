#pragma once
#include "Object.h"

class RockHead : public Object {
public:
    RockHead() : Object(Object::TRAP) {}
    virtual void Begin() override;
    virtual void Update(float deltaTime) override;
    virtual void Render(Renderer &renderer) override;
    sf::FloatRect GetBounds() const override; // Fonksiyonun geçersiz kılındığını belirtir
private:
    sf::Vector2f velocity;
    float speed = 50.0f; // Hareket hızı
    sf::RectangleShape shape;
};
