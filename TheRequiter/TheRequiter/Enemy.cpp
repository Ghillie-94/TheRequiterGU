#include "Enemy.h"

Enemy::Enemy(sf::Vector2f newPosition, Player* newPlayerPtr)
	:Animation()
	, playerPtr(newPlayerPtr)
	, playerInRange(false)
	, health()
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

void Enemy::ChangeHealth(int damage)
{
	health = health - damage;
}

void Enemy::AttackTimer()
{
	//handled in child class
}

void Enemy::DoAttack()
{
	//handled in child class
}
