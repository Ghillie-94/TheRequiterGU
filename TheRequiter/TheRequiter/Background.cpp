#include "Background.h"
#include "AssetManager.h"

Background::Background()
{
	background.setTexture(AssetManager::RequestTexture("Assets/Graphics/PromBackground.png"));
}

void Background::Draw(sf::RenderTarget& target)
{
	target.draw(background);
}
