#pragma once
#include "Parallax.h"
#include "Player.h"
class PalmTreeClose :
    public Parallax
{
public:

    PalmTreeClose(sf::Vector2f newPosition, Player* newPlayerPtr);

    void Update(sf::Time frameTime) override;

private:

    Player* playerPtr;
    float playerVelocity;
    const float SCROLLSPEED;
};

