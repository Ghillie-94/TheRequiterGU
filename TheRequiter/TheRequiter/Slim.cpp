#include "Slim.h"



Slim::Slim(sf::Vector2f newPosition, sf::Vector2f newPos1, sf::Vector2f newPos2)
	:Enemy(newPosition)
	, SPEED(80)
	, POS1(newPos1)
	, POS2(newPos2)
	, targetPoint(&POS2)
	, velocity(0, 0)
{
}

void Slim::Update(sf::Time frameTime)
{
}

void Slim::SetPosition(sf::Vector2f newPosition)
{
}
