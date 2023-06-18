#pragma once
#include "SpriteObject.h"
class Parallax :
    public SpriteObject
{
public:
    Parallax(sf::Vector2f newPosition);
    Parallax();
    void Update(sf::Time frameTime) override;
};

