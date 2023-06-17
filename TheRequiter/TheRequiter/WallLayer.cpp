#include "WallLayer.h"
#include "AssetManager.h"

WallLayer::WallLayer(sf::Vector2f newPosition, Player* newPlayerPtr)
	:Parallax()
	, playerPtr(newPlayerPtr)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Parallax/Wall.png"));
}
