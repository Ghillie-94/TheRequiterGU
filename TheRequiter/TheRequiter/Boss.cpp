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

void Boss::Update(sf::Time frameTime)
{
	CheckHealth();
	CheckDistance(playerPtr);

	if (!playerInRange)
	{
		float frameSeconds = frameTime.asSeconds();

		sf::Vector2f newPos = GetPosition();

		sf::Vector2f toMove = velocity * frameSeconds;
		float squareDistToMove = VectorHelper::SquareMagnitude(toMove);

		sf::Vector2f vectorToTarget = *targetPoint - newPos;
		float squareDistToTarget = VectorHelper::SquareMagnitude(vectorToTarget);

		if (squareDistToMove >= squareDistToTarget)
		{
			// We arrived!

			// Set us to be on the target point
			newPos = *targetPoint;

			// Change our target point to be the other one
			if (targetPoint == &POS1)
				targetPoint = &POS2;
			else
				targetPoint = &POS1;
		}
		else
		{
			newPos += toMove;
		}

		SetPosition(newPos);
	}
	else
	{
		//TODO move towards player
	}
}

void Boss::SetPosition(sf::Vector2f newPosition)
{
	Enemy::SetPosition(newPosition);

	// Update velocity
	sf::Vector2f vectorToNewTarget = *targetPoint - GetPosition();
	vectorToNewTarget = VectorHelper::Normalise(vectorToNewTarget);
	velocity = vectorToNewTarget * SPEED;
}

void Boss::CheckHealth()
{
	if (health <= 0)
	{
		Die();
	}
	return;
}

void Boss::ChangeHealth(int damage)
{
	health = health - damage;
}

void Boss::AttackTimer()
{
	if (hasAttacked)
	{
		cooldownClock.getElapsedTime() = cooldownTimer;
		if (cooldownTimer > sf::seconds(3.5f))
		{
			SetHasAttacked(false);
		}

	}
}

void Boss::DoAttack()
{
	if (canAttack && !hasAttacked)
	{
		playerPtr->ChangeHealth(35);
		SetHasAttacked(true);
		cooldownClock.restart();
		AttackTimer();

	}
}

void Boss::AttackCheck()
{
}

void Boss::CheckDistance(Player* newPlayerPtr)
{
	bool leftSideEnemy = false;
	int targetRange = 300;
	playerPtr = newPlayerPtr;
	float left;
	float right;
	float playerPosition = playerPtr->GetPosition().x;
	float platformPos = GetPosition().x;
	if (platformPos < playerPosition)
	{
		leftSideEnemy = true;
	}
	if (!leftSideEnemy)
	{
		left = playerPosition;
		right = platformPos;
	}
	else
	{
		right = playerPosition;
		left = platformPos;
	}
	if ((right - left) < targetRange)
	{
		SetInRange(true);
	}
	else
	{
		SetInRange(false);
	}
}

void Boss::SetCanAttack(bool newCanAttack)
{
	canAttack = newCanAttack;
}

void Boss::SetHasAttacked(bool newHasAttacked)
{
	hasAttacked = newHasAttacked;
}


