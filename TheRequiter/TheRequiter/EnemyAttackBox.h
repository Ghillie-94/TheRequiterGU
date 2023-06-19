#pragma once
#include "SpriteObject.h"

class Enemy;
class EnemyAttackBox :
    public SpriteObject
{
public:
    EnemyAttackBox(Enemy* newEnemyPtr);

    void HandleCollision(SpriteObject& other) override;

private:

    Enemy* enemyPtr;
};

