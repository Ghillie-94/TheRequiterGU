#include "PlayerAttackBox.h"

PlayerAttackBox::PlayerAttackBox(Player* newPlayerPtr)
	:SpriteObject()
	, playerPtr(newPlayerPtr)
{
	collisionOffset = sf::Vector2f(50, 0);
	collisionScale = sf::Vector2f(0.5f, 0.5f);
	collisionType = CollisionType::AABB;
}

void PlayerAttackBox::HandleCollision(SpriteObject& other)
{
	playerPtr->SetCanAttack(true);
	
}
