#pragma once
#include "Animation.h"
#include "Player.h"

class Enemy :
    public Animation
{
public:
    Enemy(sf::Vector2f newPosition, Player* newPlayerPtr);

    void SetInRange(bool newPlayerInRange);
    void Die();

    virtual void ChangeHealth(int damage);
    virtual void AttackTimer();
    virtual void DoAttack();
    virtual void AttackCheck();


private:
    Player* playerPtr;
    bool playerInRange;
    int health;
};

