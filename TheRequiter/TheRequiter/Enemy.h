#pragma once
#include "Animation.h"
#include "Player.h"

class Enemy :
    public Animation
{
public:
    Enemy(sf::Vector2f newPosition, Player* newPlayerPtr);

    
    void Die();

private:
    Player* playerPtr;
};

