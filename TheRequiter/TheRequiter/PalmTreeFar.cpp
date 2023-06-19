#include "PalmTreeFar.h"
#include "AssetManager.h"

PalmTreeFar::PalmTreeFar(sf::Vector2f newPosition, Player* newPlayerPtr)
	: Parallax()
	, playerPtr(newPlayerPtr)
	, playerVelocity(0)
	, SCROLLSPEED(30)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Parallax/PalmTreeFar.png"));
	SetPosition(newPosition);
}

void PalmTreeFar::Update(sf::Time frameTime)
{
	playerVelocity = playerPtr->GetVelocity().x;
	if (playerVelocity > 0)
	{
		this->sprite.move(SCROLLSPEED, 0);
	}
	else if (playerVelocity < 0)
	{
		this->sprite.move(-SCROLLSPEED, 0);
	}
}
