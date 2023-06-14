#pragma once
#include "SpriteObject.h"
#include <SFML/Graphics.hpp>
#include "Player.h"

class PlayerAttackBox :
    public SpriteObject
{
public:
    PlayerAttackBox(Player* newPlayerPtr);

    void HandleCollision(SpriteObject& other) override;

private:

    Player* playerPtr;

};

