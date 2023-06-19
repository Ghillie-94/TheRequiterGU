#include "PalmTreeFar.h"
#include "AssetManager.h"

PalmTreeFar::PalmTreeFar(sf::Vector2f newPosition, Player* newPlayerPtr)
	: Parallax()
	, playerPtr(newPlayerPtr)
	, playerVelocity(0)
	, SCROLLSPEED(10)
	
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Parallax/PalmTreeFar.png"));
	sprite.scale(.25, .25);
	SetPosition(newPosition);
	pos = GetPosition();
	drawCollider = false;
}

void PalmTreeFar::Update(sf::Time frameTime)
{
	playerVelocity = playerPtr->GetVelocity().x;
	if (playerVelocity > 0)
	{
		sprite.setPosition(pos.x - SCROLLSPEED, pos.y);
	}
	else if (playerVelocity < 0)
	{
		sprite.setPosition(pos.x + SCROLLSPEED, pos.y);
	}
}
