#include "PlayerAttackBox.h"

PlayerAttackBox::PlayerAttackBox()
	:SpriteObject()
{
	collisionOffset = sf::Vector2f(50, 0);
	collisionScale = sf::Vector2f(0.5f, 0.5f);
	collisionType = CollisionType::AABB;
}
