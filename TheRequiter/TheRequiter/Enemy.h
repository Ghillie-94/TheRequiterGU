#pragma once
#include "Animation.h"




class LevelScreen;
class Player;
class Enemy :
    public Animation
{
public:
    Enemy(sf::Vector2f newPosition, Player* newPlayerPtr, LevelScreen* newLevelScreen);

    void SetInRange(bool newPlayerInRange);
    void Die();

    virtual void ChangeHealth(int damage);
    virtual void CheckHealth();
    virtual void AttackTimer();
    virtual void DoAttack();
    virtual void AttackCheck(Player& player);
    virtual void SetCanAttack(bool newCanAttack);

protected:
    bool playerInRange;
    bool canAttack;
    


private:
    Player* playerPtr;
    
    int health;
    LevelScreen* levelScreen;
};

