//
// Created by kagan on 4.06.2024.
//

#include "Character.h"

#include "Physics.h"
#include "Resources.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_world.h"
#include "box2d/b2_fixture.h"
#include "fmt/printf.h"


const float movementSpeed = 100.0f;
const float jumpVelocity = 100.0f;


void Character::Begin() {
    b2BodyDef body_def{};

    body_def.type = b2_dynamicBody;
    body_def.position.Set(position.x, position.y);
    body_def.fixedRotation = true;
    body = Physics::world.CreateBody(&body_def);

    b2PolygonShape shape{};
    shape.SetAsBox(11, 16);

    b2FixtureDef fixture_def{};
    fixture_def.shape = &shape;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;
    body->CreateFixture(&fixture_def);


    b2CircleShape circleShape{};
    circleShape.m_radius = 5.0f;
    circleShape.m_p.Set(0.0f, -11.5f);
    fixture_def.shape = &circleShape;
    body->CreateFixture(&fixture_def);

    circleShape.m_p.Set(0.0f, 11.5f);
    fixture_def.userData;
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
        velocity.y = -jumpVelocity;

    body->SetLinearVelocity(velocity);


    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() * (180.0f / M_PI);



}

void Character::Draw(Renderer &renderer) {
    renderer.Draw(Resources::textures["idle1.png"], position, sf::Vector2f(32.0f, 32.0f), angle);
}



