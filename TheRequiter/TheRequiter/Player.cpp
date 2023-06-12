#include "Player.h"
#include "AssetManager.h"

enum class PhysicsType
{
	FORWARD_EULER,
	BACKWARD_EULER,
	SYMPLECTIC_EULER,
	POSITION_VERLET,
	VELOCITY_VERLET
};

Player::Player()
	: SpriteObject()
	, twoFramesOldPos(100, 100)
	, velocity(0, 0)
	, acceleration(0, 0)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Frank/Idle1.png"));
	collisionOffset = sf::Vector2f(0, 30);
	collisionScale = sf::Vector2f(0.5f, 0.5f);
	collisionType = CollisionType::AABB;
}

void Player::Update(sf::Time frameTime)
{
	const float DRAG_MULT = 1.0f;
	const PhysicsType physics = PhysicsType::FORWARD_EULER;

	switch (physics)
	{
	case PhysicsType::FORWARD_EULER:
	{
		// EXPLICIT EULER (FORWARD EULER)
		SetPosition(GetPosition() + velocity * frameTime.asSeconds());
		velocity = velocity + acceleration * frameTime.asSeconds();

		// drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

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

void Player::AttackCheck()
{
}

void Player::ChangeHealth()
{
}

void Player::GetVelocity()
{
}

void Player::UpdateAcceleration()
{
}
