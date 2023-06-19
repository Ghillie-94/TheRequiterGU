#include "PalmTreeClose.h"
#include "AssetManager.h"

PalmTreeClose::PalmTreeClose(sf::Vector2f newPosition, Player* newPlayerPtr)
	: Parallax()
	, playerPtr(newPlayerPtr)
	, playerVelocity(0)
	, SCROLLSPEED(20)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Parallax/PalmTreeClose.png"));
	sprite.scale(.25, .25);
	SetPosition(newPosition);
	pos = GetPosition();
	drawCollider = false;
	collisionScale = sf::Vector2f(0, 0);
}

void PalmTreeClose::Update(sf::Time frameTime)
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
