//
// Created by kagan on 5.06.2024.
//

#include "Physics.h"

#include "box2d/b2_world.h"

b2World Physics::world{b2Vec2(0.0f, 20.2f)};

void Physics::Init() {

}

void Physics::Update(float deltaTime) {
    world.Step(deltaTime, 6,2);
}
