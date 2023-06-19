#pragma once
#include "Parallax.h"
#include "Player.h"
class PalmTreeFar :
    public Parallax
{
public:
    PalmTreeFar(sf::Vector2f newPosition, Player* newPlayerPtr);

    void Update(sf::Time frameTime) override;

private:

    Player* playerPtr;
    float playerVelocity;
    const float SCROLLSPEED;
    sf::Vector2f pos;
};

