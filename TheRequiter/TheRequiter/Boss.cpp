#include "Boss.h"
#include "AssetManager.h"
#include "VectorHelper.h"

Boss::Boss(sf::Vector2f newPosition, sf::Vector2f newPos1, sf::Vector2f newPos2, Player* newPlayerPtr, LevelScreen* newLevelScreen)
	:Enemy(newPosition, newPlayerPtr, newLevelScreen)
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
	, bossAttackBox(this)
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Boss/Idle.png"));
	collisionOffset = sf::Vector2f(0, 30);
	collisionScale = sf::Vector2f(0.5f, 0.5f);
	collisionType = CollisionType::AABB;

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
	if (velocity.x != 0 || velocity.y != 0)
	{
		this->Play("Walk");
	}
	else
	{
		this->Play("Idle");
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
		levelScreen->TriggerWin(true);
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
		this->Play("Overhand");
		playerPtr->ChangeHealth(35);
		SetHasAttacked(true);
		cooldownClock.restart();
		AttackTimer();

	}
}

void Boss::AttackCheck(bool newCanAttack)
{
	canAttack = newCanAttack;
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



void Boss::SetHasAttacked(bool newHasAttacked)
{
	hasAttacked = newHasAttacked;
}

void Boss::LoadAnimation()
{
	//LOAD ANIMATIONS
	//load stand animation
	std::vector<sf::Texture> stand;
	int numOfFrames = 1;
	std::string baseFilePath = "Assets/Boss/Idle";
	std::string fileType = "png";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		stand.push_back(sf::Texture());
	}

	//load walk animation
	std::vector<sf::Texture> walk;
	numOfFrames = 4;
	baseFilePath = "Assets/Boss/Walk";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		walk.push_back(sf::Texture());
	}


	//load overhand animation
	std::vector<sf::Texture> overhand;
	numOfFrames = 3;
	baseFilePath = "Assets/Boss/Overhand";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		overhand.push_back(sf::Texture());
	}

	// current animation clip
	std::vector<sf::Texture>* currentAni = &stand;

	//animation variables
	float framesPerSecond = 12.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / framesPerSecond);
	sf::Clock aniClock;
	int currentFrame = 0;

	sf::Texture bossStandTex;
	bossStandTex.loadFromFile("Assets/Boss/Idle");
	sprite.setTexture(bossStandTex);

	//animation setup
	Animation bossAnimation(&sprite, "Assets/Boss", 12.0f);
	bossAnimation.AddClip("Idle", 1, true);
	bossAnimation.AddClip("Walk", 4, true);
	bossAnimation.AddClip("Overhand", 3, false);
}


