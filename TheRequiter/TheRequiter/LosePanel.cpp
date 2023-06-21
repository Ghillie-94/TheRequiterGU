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
	title.setString("YOU LOSE!");
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
	if (animatingIn)
	{
		float xPos = window->getSize().x * 0.5f - background.getGlobalBounds().width * 0.5f;
		float yPos = window->getSize().y;
		float finalYPos = window->getSize().y * 0.5f - background.getGlobalBounds().height * 0.5f;

		sf::Vector2f begin(xPos, yPos);
		sf::Vector2f change(0, finalYPos - yPos);
		float duration = 1.0f;
		float time = animationClock.getElapsedTime().asSeconds();

		sf::Vector2f newPosition = Easing::EaseInQuad(begin, change, duration, time);
		SetPosition(newPosition);

		if (time >= duration)
		{
			SetPosition(begin + change);
			animatingIn = false;
		}
	}

}

void LosePanel::Draw(sf::RenderTarget& target)
{

	target.draw(background);
	target.draw(message);
	target.draw(title);

}

void LosePanel::SetPosition(sf::Vector2f newPosition)
{
	background.setPosition(newPosition);

	// center the title on the x direction
	float titleX = background.getGlobalBounds().width * 0.5f - title.getGlobalBounds().width * 0.5f;
	title.setPosition(sf::Vector2f(newPosition.x + titleX, newPosition.y + 50));

	// center the message in the x and y direction
	float messageX = background.getGlobalBounds().width * 0.5f - message.getGlobalBounds().width * 0.5f;
	float messageY = background.getGlobalBounds().height * 0.5f - message.getGlobalBounds().height * 0.5f;
	message.setPosition(sf::Vector2f(newPosition.x + messageX, newPosition.y + messageY));
}

void LosePanel::StartAnimation()
{

	animatingIn = true;
	animationClock.restart();

}

void LosePanel::ResetPosition()
{

	float xPos = window->getSize().x * 0.5f - background.getGlobalBounds().width * 0.5f;
	float yPos = window->getSize().y;
	SetPosition(sf::Vector2f(xPos, yPos));

}
