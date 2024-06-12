#pragma once
#include "Renderer.h"

class Object
{
public:
    enum ObjectType {
        COLLECTABLE,
        TRAP,
        JUMP_BUFF,
    };

    Object(ObjectType type) : type(type) {}

    virtual void Begin() {}
    virtual void Update(float deltaTime) {}
    virtual void Render(Renderer& renderer) {}
    virtual sf::FloatRect GetBounds() const = 0; // Saf sanal fonksiyon

    sf::Vector2f position{};
    float angle{};
    ObjectType type; // Object type


};