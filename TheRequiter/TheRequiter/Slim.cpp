#include "Slim.h"



Slim::Slim(sf::Vector2f newPosition, sf::Vector2f newPos1, sf::Vector2f newPos2)
	:Enemy(newPosition)
	, health(75)
	, canAttack(false)
	, hasAttacked(false)
	, SPEED(80)
	, POS1(newPos1)
	, POS2(newPos2)
	, targetPoint(&POS2)
	, velocity(0, 0)
{
}

void Slim::Update(sf::Time frameTime)
{
	CheckHealth();
}

void Slim::SetPosition(sf::Vector2f newPosition)
{
}

void Slim::CheckHealth()
{
	if (health <= 0)
	{
		Die();
	}
	return;
}

void Slim::ChangeHealth(int damage)
{
	health = health - damage;
}
