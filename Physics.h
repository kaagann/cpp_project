#pragma once

#include <box2d/b2_body.h>

#include "Renderer.h"

class MyDebugDraw;

class CollisionListener {
public:

};

class Physics{
public:
    static void Init();
    static void Update(float deltaTime);
    static void DebugDraw(Renderer& renderer);
    static b2World world;
    static MyDebugDraw* debugDraw;
};
