#pragma once
#include "Screen.h"
#include "Player.h"
#include "Barrier.h"
#include "VerticalBarrier.h"
#include "WinPanel.h"
#include "LosePanel.h"
#include "Game.h"
#include "AssetManager.h"
#include "Background.h"


#include <SFML/Graphics.hpp>

class Game;
class Enemy;
class Parallax;

class LevelScreen :
    public Screen
{

public:

    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void TriggerWin(bool win);
    void TriggerLose(bool lose);
    

private:

    void Restart();
    bool LoadLevel(std::string fileName);
    bool LoadLevel(int levelNumber);
    bool LoadTitleScreen();

    bool isTitleScreen;
    bool isBossAlive;
    bool isPlayerAlive;
    bool gameRunning;

    Player player;
    WinPanel winPanel;
    LosePanel losePanel;
    Background background;

    //declare a vector array of parallax pointers
    std::vector<Parallax*> parallaxLayers;

    //declare a vector array of barrier pointers
    std::vector<Barrier*> barriers;
    std::vector<VerticalBarrier*> vBarriers;

    //declare a vector array of enemy pointers
    std::vector<Enemy*> enemies;
    

    sf::View camera;

    int currentLevel;

};

