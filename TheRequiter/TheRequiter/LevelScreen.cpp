#include "LevelScreen.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, isTitleScreen(true)
	, isBossAlive(true)
	, isPlayerAlive(true)
	, player(nullptr)
	, winPanel(newGamePointer->GetWindow())
	, losePanel(newGamePointer->GetWindow())

{
	//add restart here
}

void LevelScreen::Update(sf::Time frameTime)
{
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
}

void LevelScreen::TriggerWin(bool win)
{
	isBossAlive = false;
	winPanel.StartAnimation();
}

void LevelScreen::TriggerLose(bool lose)
{
	isPlayerAlive = false;
	losePanel.StartAnimation();
}

void LevelScreen::Restart()
{
}

void LevelScreen::LoadLevel(std::string fileName)
{
}

void LevelScreen::LoadTitleScreen()
{
}
