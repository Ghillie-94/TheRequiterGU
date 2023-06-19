#include "Enemy.h"
#include "Player.h"
#include "LevelScreen.h"

Enemy::Enemy(sf::Vector2f newPosition, Player* newPlayerPtr, LevelScreen* newLevelScreen)
	:Animation()
	, levelScreen(newLevelScreen)
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

void Enemy::CheckHealth()
{
	//handled in child class
}

void Enemy::AttackTimer()
{
	//handled in child class
}

void Enemy::DoAttack()
{
	//handled in child class
}

void Enemy::AttackCheck(bool newCanAttack)
{
	//handled in child class
}



