#include "WallLayer.h"
#include "AssetManager.h"

WallLayer::WallLayer(sf::Vector2f newPosition, Player* newPlayerPtr)
	:Parallax()
	, playerPtr(newPlayerPtr)
	, playerVelocity(0)
	, SCROLLSPEED(100)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Parallax/Wall.png"));
	SetPosition(newPosition);
}

void WallLayer::Update(sf::Time frameTime)
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

