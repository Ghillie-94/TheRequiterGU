#include "LevelScreen.h"
#include "AssetManager.h"
#include "Boss.h"
#include "Slim.h"
#include "Parallax.h"
#include "Enemy.h"

#include <fstream>
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, isTitleScreen(true)
	, isBossAlive(true)
	, isPlayerAlive(true)
	, gameRunning(true)
	, player(nullptr)
	, winPanel(newGamePointer->GetWindow())
	, losePanel(newGamePointer->GetWindow())
	, parallaxLayers()
	, currentLevel(1)
	, barriers()
	, vBarriers()
	, enemies()
	

{
	Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		if (!isTitleScreen)
		{
			if (isBossAlive)
			{
				if (player.CheckAlive() == true)
				{
					for (int i = 0; i < enemies.size(); ++i)
					{
						enemies[i]->Update();
					}

					player.SetColliding(false);
					player.SetCanAttack(false);


					for (int i = 0; i < enemies.size(); ++i)
					{
						enemies[i]->SetColliding(false);
					}

					for (int i = 0; i < barriers.size(); ++i)
					{
						barriers[i]->SetColliding(false);
					}

					for (int i = 0; i < parallaxLayers.size(); ++i)
					{
						parallaxLayers[i]->SetColliding(false);
					}

					for (int i = 0; i < enemies.size(); ++i)
					{
						if (enemies[i]->CheckCollision(player.GetPlayerAttackBox()))
						{
							player.SetCanAttack(true);
							enemies[i]->SetColliding(true);
							player.GetPlayerAttackBox().SetColliding(true);
						}

						if (enemies[i]->GetEnemyAttackBox().CheckCollision(player))
						{
							enemies[i]->AttackCheck(true);
							player.SetColliding(true);
						}


					}


				}
				else
				{
					TriggerLose(true);
					losePanel.Update(frameTime);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
					{
						Restart();
					}
				}
			}
			else
			{
				winPanel.Update(frameTime);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
				{
					Restart();
				}
			}
			
		}
	}
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
	LoadLevel(currentLevel);
}

bool LevelScreen::LoadLevel(std::string fileName)
{
	// open the level file
	std::ifstream inFile;
	std::string filePath = "Assets/Levels/" + fileName + ".txt";
	inFile.open(filePath);

	//make sure file was actually opened
	if (!inFile)
	{
		// file was not opened
		return false;
	}

	// clear out enemies before making new ones
	// Make sure to delete BEFORE clearing!
	for (int i = 0; i < enemies.size(); ++i)
	{
		delete enemies[i];
		enemies[i] = nullptr;
	}
	enemies.clear();


	//set the starting x and y coordinates used to position our level objs
	float x = 0.0f;
	float y = 0.0f;

	//define the spacing we will use for our grid
	const float X_SPACE = 150.0f;
	const float Y_SPACE = 150.0f;

	//read each character one by one from the file...
	char ch;

	//each time try to read the next character
	//if succesful, execute the body of loop
	// the no skip ws means that input from the file will inc white space

	while (inFile >> std::noskipws >> ch)
	{
		// perform actions based on what char was read in
		if (ch == ' ')
		{
			x += X_SPACE;
		}
		else if (ch == '\n')
		{
			y += Y_SPACE;
			x = 0;
		}
		else if (ch == 'P')
		{
			player.SetPosition(x, y);
		}
		else if (ch == 'W')
		{
			
		}

		else if (ch == 'S')
		{
			enemies.push_back(new Slim(sf::Vector2f(x, y), sf::Vector2f(x+100, y), sf::Vector2f(x-100, y), &player, this));
		}
		else if (ch == 'B')
		{
			enemies.push_back(new Boss(sf::Vector2f(x, y), sf::Vector2f(x+100, y), sf::Vector2f(x-100, y), &player, this));
		}
		
		else if (ch == '-')
		{
			//do nothing this is empty space
		}
		else
		{
			std::cerr << "Unrecognised char in level file: " << ch;
		}

	}



	//close the file now that we are done with it 
	inFile.close();
	//load barriers seperately as they overlap with wall layer
	barriers.push_back(new Barrier(sf::Vector2f(0, 800))), new Barrier(sf::Vector2f(0,1080));
	vBarriers.push_back(new VerticalBarrier(sf::Vector2f(0, 0))), new VerticalBarrier(sf::Vector2f(1920, 0));

	gameRunning = true;




	//return true because we successfully loaded the level
	return true;
}

bool LevelScreen::LoadLevel(int levelNumber)
{
	//construct level name from level
	std::string levelName = "Level" + std::to_string(levelNumber);

	bool success = LoadLevel(levelName);

	if (success)
	{
		currentLevel = levelNumber;
	}

	return success;
}

bool LevelScreen::LoadTitleScreen()
{
}
