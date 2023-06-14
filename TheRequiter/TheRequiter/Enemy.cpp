#include "Enemy.h"

Enemy::Enemy(sf::Vector2f newPosition)
	:Animation()
{
}



void Enemy::Die()
{
	alive = false;
}
