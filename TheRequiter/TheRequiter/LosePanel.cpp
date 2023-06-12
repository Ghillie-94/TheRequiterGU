#include "LosePanel.h"
#include "AssetManager.h"
#include "Easing.h"

LosePanel::LosePanel(sf::RenderWindow* newWindow)
	: background()
	, title()
	, message()
	, position(0, 0)
	, window(newWindow)
	, animatingIn(false)
	, animationClock()
{

	background.setTexture(AssetManager::RequestTexture("insertgraphicforpanelhere"));
	background.setScale(5.0f, 5.0f);

	title.setFont(AssetManager::RequestFont("Assets/Fonts/good-times.rg-regular.otf"));
	title.setCharacterSize(70);
	title.setString("YOU WIN!");
	title.setFillColor(sf::Color::Magenta);
	title.setOutlineColor(sf::Color::Cyan);

	message.setFont(AssetManager::RequestFont("Assets/Fonts/good-times.rg-regular.otf"));
	message.setCharacterSize(30);
	message.setString("MENU");
	message.setFillColor(sf::Color::Magenta);
	message.setOutlineColor(sf::Color::Cyan);

	ResetPosition();

}

void LosePanel::Update(sf::Time frameTime)
{
}

void LosePanel::Draw(sf::RenderTarget& target)
{
}

void LosePanel::SetPosition(sf::Vector2f newPosition)
{
}

void LosePanel::StartAnimation()
{
}

void LosePanel::ResetPosition()
{
}
