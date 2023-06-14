#include "Boss.h"
#include "AssetManager.h"
#include "VectorHelper.h"

Boss::Boss(sf::Vector2f newPosition, sf::Vector2f newPos1, sf::Vector2f newPos2, Player* newPlayerPtr)
	:Enemy(newPosition, newPlayerPtr)
	, health(180)
	, canAttack(false)
	, hasAttacked(false)
	, playerInRange(false)
	, SPEED(80)
	, POS1(newPos1)
	, POS2(newPos2)
	, targetPoint(&POS2)
	, velocity(0, 0)
	, playerPtr(newPlayerPtr)
{

	sf::Clock cooldownClock;
	sf::Time cooldownTimer;

	// Update velocity
	sf::Vector2f vectorToNewTarget = *targetPoint - GetPosition();
	vectorToNewTarget = VectorHelper::Normalise(vectorToNewTarget);
	velocity = vectorToNewTarget * SPEED;

}
