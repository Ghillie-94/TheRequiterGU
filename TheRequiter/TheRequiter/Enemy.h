#pragma once
#include "Animation.h"

class Enemy :
    public Animation
{
public:
    Enemy(sf::Vector2f newPosition);

    
    void Die();
};

