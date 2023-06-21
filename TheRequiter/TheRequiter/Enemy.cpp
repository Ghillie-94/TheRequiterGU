#include "Enemy.h"
#include "Player.h"
#include "LevelScreen.h"
#include <iostream>

Enemy::Enemy(sf::Vector2f newPosition, Player* newPlayerPtr, LevelScreen* newLevelScreen)
	:Animation("Assets/Graphics/Enemies/", 6, "png")
	, levelScreen(newLevelScreen)
	, playerPtr(newPlayerPtr)
	, playerInRange(false)
	, health()
{
	SetPosition(newPosition);
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
	std::cout << "Enemy health reduced by" << damage << std::endl;
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



