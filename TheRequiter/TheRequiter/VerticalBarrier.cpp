#include "VerticalBarrier.h"
#include "AssetManager.h"

VerticalBarrier::VerticalBarrier(sf::Vector2f newPosition)
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Vbarrier.png"));
}
