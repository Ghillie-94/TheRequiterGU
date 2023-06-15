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
