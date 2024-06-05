//
// Created by kagan on 4.06.2024.
//

#include "Character.h"

#include "Physics.h"
#include "Resources.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_world.h"
#include "box2d/b2_fixture.h"
#include "fmt/printf.h"

const float movementSpeed = 30.0f;


void Character::Begin() {
    b2BodyDef body_def{};
    body_def.type = b2_dynamicBody;
    body_def.position.Set(position.x, position.y);
    body_def.fixedRotation = true;
    body = Physics::world.CreateBody(&body_def);
    b2PolygonShape shape{};
    shape.SetAsBox(8, 8);
    b2FixtureDef fixture_def{};
    fixture_def.shape = &shape;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;
    body->CreateFixture(&fixture_def);
}

void Character::Update(float deltaTime) {
    float move = movementSpeed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        move *= 2;

    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += move;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= move;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        body->ApplyForceToCenter(b2Vec2(0.0f, -move * 10.0f), true);

    body->SetLinearVelocity(velocity);




    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() * (180.0f / M_PI);



}

void Character::Draw(Renderer &renderer) {
    renderer.Draw(Resources::textures["idle.png"], position, sf::Vector2f(16.0f, 16.0f), sf::IntRect(0,0,32,32), angle);
}



