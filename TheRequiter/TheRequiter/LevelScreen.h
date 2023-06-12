#pragma once
#include "Screen.h"
#include "Player.h"
#include "Barrier.h"
#include "WinPanel.h"
#include "LosePanel.h"
#include "Game.h"
#include "AssetManager.h"

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
    void LoadLevel(std::string fileName);
    void LoadTitleScreen();

    bool isTitleScreen;
    bool isBossAlive;
    bool isPlayerAlive;

    Player player;
    WinPanel winPanel;
    LosePanel losePanel;

    //declare a vector array of parallax pointers
    std::vector<Parallax*> parallaxLayers;

    //declare a vector array of enemy pointers
    std::vector<Enemy*> enemies;
    

    sf::View camera;

};

