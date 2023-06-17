#pragma once
#include "Animation.h"
#include "Player.h"
#include "LevelScreen.h"
#include "EnemyAttackBox.h"

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
    virtual void AttackCheck(bool newCanAttack);
    virtual EnemyAttackBox GetEnemyAttackBox();


private:
    Player* playerPtr;
    bool playerInRange;
    int health;
    LevelScreen* levelScreen;
};

