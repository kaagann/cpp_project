#pragma once
#include "Object.h"

class EndPoint : public Object {
public:
    EndPoint() : Object(Object::END_POINT) {}
    virtual void Begin() override;
    virtual void Update(float deltaTime) override;
    virtual void Render(Renderer &renderer) override;
    sf::FloatRect GetBounds() const override; // Fonksiyonun geçersiz kılındığını belirtir
};
