#pragma once
#include <SFML/Graphics.hpp>

enum class CollisionType
{
	CIRCLE,
	AABB
};

class SpriteObject
{

public:

	SpriteObject();

	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	sf::Vector2f GetPosition();
	virtual void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newX, float newY);

	bool CheckCollision(SpriteObject other);
	void SetColliding(bool newColliding);

	sf::Vector2f GetCollisionDepth(SpriteObject other);
	virtual void HandleCollision(SpriteObject& other);
	void SetAlive(bool newAlive);
	void SetColliderDraw(bool newDrawCollider);
	sf::FloatRect GetAABB();
	


protected:

	sf::Sprite sprite;
	sf::Vector2f collisionOffset;
	sf::Vector2f collisionScale;
	CollisionType collisionType;
	bool alive;
	bool drawCollider;
	

private:

	sf::Vector2f GetCollisionCentre();
	float GetCircleColliderRadius();
	
	sf::Vector2f position;
	bool colliding;

};

