#pragma once
#include "Parallax.h"
#include "Player.h"
class WallLayer :
    public Parallax
{
public:

    WallLayer(sf::Vector2f newPosition, Player* newPlayerPtr);

private:
    
    Player* playerPtr
};

