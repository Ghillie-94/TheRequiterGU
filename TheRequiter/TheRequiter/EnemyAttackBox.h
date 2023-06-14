#pragma once
#include "SpriteObject.h"
#include "Enemy.h"
class EnemyAttackBox :
    public SpriteObject
{
public:
    EnemyAttackBox(Enemy* newEnemyPtr);

    void HandleCollision(SpriteObject& other) override;

private:

    Enemy* enemyPtr;
};

