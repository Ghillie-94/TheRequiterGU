#include "PierFerrisLayer.h"

PierFerrisLayer::PierFerrisLayer(sf::Vector2f newPosition, Player* newPlayerPtr)
	: Parallax()
	, playerPtr(newPlayerPtr)
	, playerVelocity(0)
	, SCROLLSPEED(50)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Parallax/PierFerrisLayer.png"));
	SetPosition(newPosition);
}

void PierFerrisLayer::Update(sf::Time frameTime)
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
