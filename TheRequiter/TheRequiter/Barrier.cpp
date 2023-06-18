#include "Barrier.h"
#include "AssetManager.h"

Barrier::Barrier(sf::Vector2f newPosition)
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Barrier.png"));
	SetPosition(newPosition);
}
