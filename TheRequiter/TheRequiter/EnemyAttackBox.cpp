#include "EnemyAttackBox.h"
#include "Enemy.h"

EnemyAttackBox::EnemyAttackBox(Enemy* newEnemyPtr)
	: SpriteObject()
	, enemyPtr(newEnemyPtr)
{
}

void EnemyAttackBox::HandleCollision(SpriteObject& other)
{
	enemyPtr->AttackCheck(true);
}
