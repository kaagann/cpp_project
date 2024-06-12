//
// Created by kagan on 8.06.2024.
//
#pragma once
#include "Animation.h"
#include "Object.h"


class OrangeItem : public Object {
public:
    OrangeItem() : Object(Object::JUMP_BUFF) {}

    virtual void Begin() override;
    virtual void Update(float deltaTime) override;
    virtual void Render(Renderer &renderer) override;
    sf::FloatRect GetBounds() const override; // Fonksiyonun geçersiz kılındığını belirtir
private:
    Animation animation;

};

