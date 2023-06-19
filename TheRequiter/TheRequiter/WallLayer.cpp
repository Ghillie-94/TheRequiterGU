#include "WallLayer.h"
#include "AssetManager.h"

WallLayer::WallLayer(sf::Vector2f newPosition, Player* newPlayerPtr)
	:Parallax()
	, playerPtr(newPlayerPtr)
	, playerVelocity(0)
	, SCROLLSPEED(100)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Parallax/Wall.png"));
	sprite.scale(.5, .5);
	SetPosition(newPosition);
	pos = GetPosition();
	drawCollider = false;
	collisionScale = sf::Vector2f(0, 0);
}

void WallLayer::Update(sf::Time frameTime)
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

