#include "Enemy.h"

Enemy::Enemy(sf::Vector2f newPosition, Player* newPlayerPtr)
	:Animation()
	, playerPtr(newPlayerPtr)
{
}



void Enemy::SetInRange(bool newPlayerInRange)
{
	playerInRange = newPlayerInRange;
}

void Enemy::Die()
{
	alive = false;
}
