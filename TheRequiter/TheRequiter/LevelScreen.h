#pragma once
#include "Screen.h"
#include "Player.h"
#include "Boss.h"
#include ""
#include <SFML/Graphics.hpp>

class Game;

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

    

    sf::View camera;

};

