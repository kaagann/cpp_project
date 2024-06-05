//
// Created by kagan on 5.06.2024.
//

#include "Physics.h"

#include "box2d/b2_draw.h"
#include "box2d/b2_world.h"

b2World Physics::world{b2Vec2(0.0f, 200.2f)};
MyDebugDraw* Physics::debugDraw{};

class MyDebugDraw
	: public b2Draw
{
public:
	MyDebugDraw(sf::RenderTarget& target)
		: target(target)
	{
	}

	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount,
		const b2Color& color) override
	{
		sf::ConvexShape shape(vertexCount);
		for (int i = 0; i < vertexCount; i++)
		{
			shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
		}

		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(1.0f);
		shape.setOutlineColor(sf::Color((sf::Uint8)(color.r * 255),
			(sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255),
			(sf::Uint8)(color.a * 255)));
		target.draw(shape);
	}

	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
		const b2Color& color) override
	{
		sf::ConvexShape shape(vertexCount);
		for (int i = 0; i < vertexCount; i++)
		{
			shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
		}

		shape.setFillColor(sf::Color((sf::Uint8)(color.r * 255),
			(sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255),
			(sf::Uint8)(color.a * 120)));
		target.draw(shape);
	}

	virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override
	{
		sf::CircleShape circle(radius);
		circle.setPosition(center.x, center.y);
		circle.setOrigin(radius, radius);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineThickness(1.0f);
		circle.setOutlineColor(sf::Color((sf::Uint8)(color.r * 255),
			(sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255),
			(sf::Uint8)(color.a * 255)));
		target.draw(circle);
	}

	virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override
	{
		sf::CircleShape circle(radius);
		circle.setPosition(center.x, center.y);
		circle.setOrigin(radius, radius);
		circle.setFillColor(sf::Color((sf::Uint8)(color.r * 255),
			(sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255),
			(sf::Uint8)(color.a * 120)));
		target.draw(circle);

		b2Vec2 p = center + (radius * axis);
		DrawSegment(center, p, color);
	}

	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override
	{
		sf::VertexArray va(sf::Lines, 2);
		sf::Color sfColor = sf::Color((sf::Uint8)(color.r * 255),
			(sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255),
			(sf::Uint8)(color.a * 120));

		va[0].position = sf::Vector2f(p1.x, p1.y);
		va[0].color = sfColor;

		va[1].position = sf::Vector2f(p2.x, p2.y);
		va[1].color = sfColor;

		target.draw(va);
	}

	virtual void DrawTransform(const b2Transform& xf) override
	{
		b2Vec2 p = xf.p;
		b2Vec2 px = p + (0.5f * xf.q.GetXAxis());
		b2Vec2 py = p + (0.5f * xf.q.GetYAxis());

		DrawSegment(p, px, b2Color(1.0f, 0.0f, 0.0f));
		DrawSegment(p, py, b2Color(0.0f, 1.0f, 0.0f));
	}

	virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override
	{
		sf::CircleShape circle(size);
		circle.setPosition(p.x, p.y);
		circle.setOrigin(size, size);
		circle.setFillColor(sf::Color((sf::Uint8)(color.r * 255), (sf::Uint8)(color.g * 255), (sf::Uint8)(color.b * 255),
			(sf::Uint8)(color.a * 120)));
		target.draw(circle);
	}

private:
	sf::RenderTarget& target;
};

void Physics::Init() {

}

void Physics::Update(float deltaTime) {
    world.Step(deltaTime, 6,2);
}

void Physics::DebugDraw(Renderer& renderer)
{
	if (!debugDraw)
	{
		debugDraw = new MyDebugDraw(renderer.target);
		debugDraw->SetFlags(0u);
		world.SetDebugDraw(debugDraw);
	}

	world.DebugDraw();
}
