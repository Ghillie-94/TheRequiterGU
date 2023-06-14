#include "Enemy.h"

Enemy::Enemy(sf::Vector2f newPosition, Player* newPlayerPtr)
	:Animation()
	, playerPtr(newPlayerPtr)
{
}



void Enemy::Die()
{
	alive = false;
}
