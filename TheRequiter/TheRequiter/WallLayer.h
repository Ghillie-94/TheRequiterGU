#pragma once
#include "Parallax.h"
#include "Player.h"
class WallLayer :
    public Parallax
{
public:

    WallLayer(sf::Vector2f newPosition, Player* newPlayerPtr);

    void Update(sf::Time frameTime) override;

private:
    
    Player* playerPtr;
    float playerVelocity;
    const float SCROLLSPEED;
    sf::Vector2f pos;
};

