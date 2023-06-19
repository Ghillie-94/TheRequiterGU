#include "PalmTreeClose.h"
#include "AssetManager.h"

PalmTreeClose::PalmTreeClose(sf::Vector2f newPosition, Player* newPlayerPtr)
	: Parallax()
	, playerPtr(newPlayerPtr)
	, playerVelocity(0)
	, SCROLLSPEED(70)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Parallax/PalmTreeClose.png"));
	SetPosition(newPosition);
}

void PalmTreeClose::Update(sf::Time frameTime)
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
