#include "Slim.h"
#include "VectorHelper.h"
#include "Player.h"
#include "AssetManager.h"



Slim::Slim(sf::Vector2f newPosition, sf::Vector2f newPos1, sf::Vector2f newPos2, Player* newPlayerPtr, LevelScreen* newLevelScreen)
	:Enemy(newPosition, newPlayerPtr, newLevelScreen)
	, health(75)
	, canAttack(false)
	, hasAttacked(false)
	, playerInRange(false)
	, SPEED(80)
	, POS1(newPos1)
	, POS2(newPos2)
	, targetPoint(&POS2)
	, velocity(0, 0)
	, playerPtr(newPlayerPtr)
	, attackBox(this)
{
	sf::Clock cooldownClock;
	sf::Time cooldownTimer;

	// Update velocity
	sf::Vector2f vectorToNewTarget = *targetPoint - GetPosition();
	vectorToNewTarget = VectorHelper::Normalise(vectorToNewTarget);
	velocity = vectorToNewTarget * SPEED;
	LoadAnimation();
}

void Slim::Update(sf::Time frameTime)
{
	CheckHealth();
	CheckDistance(playerPtr);
	if (velocity.x != 0 || velocity.y != 0)
	{
		this->Play("Walk");
	}
	else
	{
		this->Play("Stand");
	}

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
		if (canAttack)
		{
			DoAttack();
		}
	}
}

void Slim::SetPosition(sf::Vector2f newPosition)
{
	Enemy::SetPosition(newPosition);

	// Update velocity
	sf::Vector2f vectorToNewTarget = *targetPoint - GetPosition();
	vectorToNewTarget = VectorHelper::Normalise(vectorToNewTarget);
	velocity = vectorToNewTarget * SPEED;
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

void Slim::AttackTimer()
{
	if (hasAttacked)
	{
		cooldownClock.getElapsedTime() = cooldownTimer;
		if (cooldownTimer > sf::seconds(2.5f))
		{
			SetHasAttacked(false);
		}

	}
}

void Slim::DoAttack()
{
	if (canAttack && !hasAttacked)
	{
		this->Play("Jab");
		playerPtr->ChangeHealth(15);
		SetHasAttacked(true);
		cooldownClock.restart();
		AttackTimer();

	}
}

void Slim::AttackCheck(bool newCanAttack)
{
	canAttack = newCanAttack;
}

void Slim::CheckDistance(Player* newPlayerPtr)
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



void Slim::SetHasAttacked(bool newHasAttacked)
{
	hasAttacked = newHasAttacked;
}



void Slim::LoadAnimation()
{
	//LOAD ANIMATIONS
	//load stand animation
	/*
	std::vector<sf::Texture> stand;
	int numOfFrames = 1;
	std::string baseFilePath = "Assets/Graphics/Slim/Idle";
	std::string fileType = "png";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		stand.push_back(sf::Texture());
	}

	//load walk animation
	std::vector<sf::Texture> walk;
	numOfFrames = 4;
	baseFilePath = "Assets/Graphics/Slim/Walk";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		walk.push_back(sf::Texture());
	}

	//load jab animation
	std::vector<sf::Texture> jab;
	numOfFrames = 3;
	baseFilePath = "Assets/Graphics/SlimJab";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		jab.push_back(sf::Texture());
	}


	// current animation clip
	std::vector<sf::Texture>* currentAni = &stand;

	*/
	//animation variables
	float framesPerSecond = 12.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / framesPerSecond);
	sf::Clock aniClock;
	int currentFrame = 0;

	
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Enemies/sIdle"));

	//animation setup
	
	AddClip("sIdle", 1, true);
	AddClip("sWalk", 4, true);
	AddClip("sJab", 3, false);
	
}




