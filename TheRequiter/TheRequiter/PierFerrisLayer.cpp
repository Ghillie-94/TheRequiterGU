#include "PierFerrisLayer.h"
#include "AssetManager.h"

PierFerrisLayer::PierFerrisLayer(sf::Vector2f newPosition, Player* newPlayerPtr)
	: Parallax()
	, playerPtr(newPlayerPtr)
	, playerVelocity(0)
	, SCROLLSPEED(20)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Parallax/PierFerrisLayer.png"));
	sprite.scale(.25, .25);
	SetPosition(newPosition);
	drawCollider = false;
	pos = GetPosition();
	
}

void PierFerrisLayer::Update(sf::Time frameTime)
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
