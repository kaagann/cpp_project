#pragma once
#include "Object.h"

class Spike : public Object {
public:
    Spike() : Object(Object::TRAP) {}
    virtual void Begin() override;
    virtual void Update(float deltaTime) override;
    virtual void Render(Renderer &renderer) override;
    sf::FloatRect GetBounds() const override; // Fonksiyonun geçersiz kılındığını belirtir
};
