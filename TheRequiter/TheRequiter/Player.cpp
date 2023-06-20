#include "Player.h"
#include "AssetManager.h"
#include "Animation.h"
#include "Enemy.h"
#include <iostream>

enum class PhysicsType
{
	FORWARD_EULER,
	BACKWARD_EULER,
	SYMPLECTIC_EULER,
	POSITION_VERLET,
	VELOCITY_VERLET
};

Player::Player(Enemy* newEnemyPtr)
	: Animation("Assets/Graphics/Frank/", 6, "png")
	, twoFramesOldPos(100, 100)
	, velocity(0, 0)
	, acceleration(0, 0)
	, attackArea()
	, attackBox(this)
	, hasAttacked(false)
	, health(200)
	, hasMovedRight(false)
	, enemyPtr(newEnemyPtr)
	
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Frank/Idle1.png"));
	sprite.scale(.5, .5);
	
	collisionType = CollisionType::AABB;
	
	attackArea.height = 150;
	attackArea.width = 150;
	
	sf::Clock cooldownClock;
	sf::Time cooldownTimer;
	

	

	LoadAnimation();
	
}

void Player::Update(sf::Time frameTime)
{
	
	const float DRAG_MULT = 5.0f;
	const PhysicsType physics = PhysicsType::FORWARD_EULER;
	attackArea.left = (GetPosition().x + 50);
	//call animation update for player
	Animation::Update(frameTime);
	//Attack input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		JabAttack();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		OverhandAttack();
	}

	switch (physics)
	{
	case PhysicsType::FORWARD_EULER:
	{
		// EXPLICIT EULER (FORWARD EULER)
		SetPosition(GetPosition() + velocity * frameTime.asSeconds());
		velocity = velocity + acceleration * frameTime.asSeconds();

		// drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
		velocity.y = velocity.y - velocity.y * DRAG_MULT * frameTime.asSeconds();

		// Update acceleration
		UpdateAcceleration();
	}
	break;

	case PhysicsType::BACKWARD_EULER:
	{
		// IMPLICIT / BACKWARD EULER

		// Update acceleration
		UpdateAcceleration();

		velocity = velocity + acceleration * frameTime.asSeconds();

		// drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

		SetPosition(GetPosition() + velocity * frameTime.asSeconds());

	}
	break;

	case PhysicsType::SYMPLECTIC_EULER:
	{
		// SEMI-IMPLICIT / SYMPLECTIC_EULER

		velocity = velocity + acceleration * frameTime.asSeconds();

		// drag
		velocity = velocity - velocity * DRAG_MULT * frameTime.asSeconds();

		SetPosition(GetPosition() + velocity * frameTime.asSeconds());

		// Update acceleration
		UpdateAcceleration();
	}
	break;

	case PhysicsType::POSITION_VERLET:
	{
		// Update acceleration
		UpdateAcceleration();

		sf::Vector2f lastFramePos = GetPosition();

		// Calculate current fram's position
		SetPosition(2.0f * lastFramePos - twoFramesOldPos + acceleration * frameTime.asSeconds() * frameTime.asSeconds());

		// Two frames ago (for next frame)
		twoFramesOldPos = lastFramePos;
	}
	break;

	case PhysicsType::VELOCITY_VERLET:
	{
		// VELOCITY VERLET / LEAP FROG

		// Get half frame velocity using
		// previous frame's acceleration
		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

		// Get new frame's position using half frame velocity
		SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());

		// Update our current acceleration
		UpdateAcceleration();

		// Get new frame's velocity using half frame velocity and
		// updated acceleration
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

		// drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
	}
	break;

	default:
		break;
	}
}

void Player::HandleCollision(SpriteObject& other)
{
	
	const float REBOUNDSPEED = 100;
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPos = GetPosition();

	if (abs(depth.x) < abs(depth.y))
	{
		// Move in X direction
		newPos.x += depth.x;
		velocity.x = 0;
		acceleration.x = 0;
	}
	else
	{
		// Move in y direction
		newPos.y += depth.y;
		velocity.y = 0;
		acceleration.y = 0;

		// If we collided from above
		if (depth.y < 0)
		{
			velocity.y = -REBOUNDSPEED;
		}
	}

	SetPosition(newPos);
}

void Player::SetCanAttack(bool newCanAttack)
{
	canAttack = newCanAttack;
}

void Player::SetHasAttacked(bool newHasAttacked)
{
	hasAttacked = newHasAttacked;
}

void Player::JabAttack()
{
	if (!hasAttacked)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			Play("Jab");
			if (canAttack)
			{
				Play("Jab");
				enemyPtr->ChangeHealth(20);
				SetHasAttacked(true);
				cooldownClock.restart();
				AttackCooldown();
				std::cout << "Jab successfully thrown" << std::endl;
			}
			else
			{
				AttackCooldown();
			}
		}
			
		
		
		
	}
}

void Player::AttackCooldown()
{
	if (hasAttacked)
	{
		cooldownClock.getElapsedTime() = coolDownTimer;
		if (coolDownTimer > sf::seconds(1.5f)) 
		{
			SetHasAttacked(false);
		}

	}
}


void Player::OverhandAttack()
{
	if (!hasAttacked)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		{
			Play("Overhand");
			if (canAttack)
			{
				enemyPtr->ChangeHealth(40);
				SetHasAttacked(true);
				cooldownClock.restart();
				AttackCooldown();
				std::cout << "Overhand successfully thrown" << std::endl;
			}
			else
			{
				AttackCooldown();
			}
			
		}
	}
}

bool Player::CheckAlive()
{
	if (this->alive == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

PlayerAttackBox Player::GetPlayerAttackBox()
{
	return attackBox;
}


void Player::AttackCheck(Enemy& other)
{
	//For attacking - use a rectangle representing the player's attack area, and set it's position to the player's plus an offset
	//You will need a function on the Player to check if the attack is hitting a particular enemy
	//have a bool for whether that attack is active
	//Set that bool to true in the update function if they pressed the button down, otherwise set it to false
	//so it will only be true for one frame.
	
	if (attackArea.intersects(other.GetAABB()))
	{
		enemyPtr = &other;
		SetCanAttack(true);
		
	}
	else
	{
		SetCanAttack(false);
	}


}




void Player::ChangeHealth(int damage)
{
	health = health - damage;
}

sf::Vector2f Player::GetVelocity()
{
	return velocity;
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 1000.0f;
	// Update acceleration
	acceleration.x = 0;
	acceleration.y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration.x = -ACCEL;
		//Play("Walk");

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration.x = ACCEL;
		//Play("Walk");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		acceleration.y = -ACCEL;
		//Play("Walk");

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		acceleration.y = ACCEL;
		//Play("Walk");
	}
	if (velocity.x != 0 || velocity.y != 0)
	{
		Play("Walk");
	}
	else if (velocity.x == 0 && velocity.y == 0)
	{
		Play("Idle");
	}

}

void Player::LoadAnimation()
{
	//LOAD ANIMATIONS
	//load stand animation
	/*
	std::vector<sf::Texture> stand;
	int numOfFrames = 2;
	std::string baseFilePath = "Assets/Graphics/Frank/Idle";
	std::string fileType = "png";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		stand.push_back(AssetManager::RequestTexture(baseFilePath + std::to_string(i) + fileType));
	}

	//load walk animation
	std::vector<sf::Texture> walk;
	numOfFrames = 4;
	baseFilePath = "Assets/Graphics/Frank/Walk";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		walk.push_back(AssetManager::RequestTexture(baseFilePath + std::to_string(i) + fileType));
	}

	//load jab animation
	std::vector<sf::Texture> jab;
	numOfFrames = 3;
	baseFilePath = "Assets/Graphics/Frank/Jab";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		jab.push_back(sf::Texture());
	}

	//load overhand animation
	std::vector<sf::Texture> overhand;
	numOfFrames = 3;
	baseFilePath = "Assets/Graphics/Frank/Overhand";

	//create loop to populate vector
	for (int i = 0; i < numOfFrames; ++i)
	{
		overhand.push_back(AssetManager::RequestTexture(baseFilePath + std::to_string(i) + fileType));
	}

	// current animation clip
	std::vector<sf::Texture>* currentAni = &stand;
	*/
	//animation variables
	float framesPerSecond = 12.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / framesPerSecond);
	sf::Clock aniClock;
	int currentFrame = 0;

	
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Frank/Idle1.png"));

	//animation setup
	
	
	AddClip("Idle", 2, true);
	AddClip("Walk", 4, false);
	AddClip("Jab", 3, false);
	AddClip("Overhand", 3, false);


}
