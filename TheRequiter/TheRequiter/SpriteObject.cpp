#include "SpriteObject.h"

SpriteObject::SpriteObject()
	: sprite()
	, position(0,0)
	, colliding(false)
	, collisionOffset(0,0)
	, collisionScale(1,1)
	, collisionType(CollisionType::AABB)
	, alive(true)
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{

	if (!alive)
		return;
	target.draw(sprite);

	bool drawCollider = true;

	if (drawCollider) 
	{
		switch (collisionType) 
		{
		case CollisionType::CIRCLE:
		{

			sf::CircleShape circle;

			sf::Vector2f shapePosition = GetCollisionCentre();
			float circleRadius = GetCircleColliderRadius();
			shapePosition.x -= circleRadius;
			shapePosition.y -= circleRadius;
			circle.setPosition(shapePosition);
			circle.setRadius(circleRadius);
			sf::Color collisionColor = sf::Color::Green;
			// turn this red if a collision is occurring
			if (colliding)
				collisionColor = sf::Color::Red;
			collisionColor.a = 100;
			circle.setFillColor(collisionColor);

			target.draw(circle);
			
		}
		break;
		case CollisionType::AABB:
		{
			sf::RectangleShape rectangle;
			sf::FloatRect bounds = GetAABB();
			rectangle.setPosition(bounds.left, bounds.top);
			rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));
			sf::Color collisionColor = sf::Color::Green;
			// turn this red if a collision is occurring
			if (colliding)
				collisionColor = sf::Color::Red;
			collisionColor.a = 100;
			rectangle.setFillColor(collisionColor);

			target.draw(rectangle);
		}
			break;
		default:
			break;
		}
			

	}
}
