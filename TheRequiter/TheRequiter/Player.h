#pragma once
#include "SpriteObject.h"
#include "Animation.h"
#include "PlayerAttackBox.h"


class Enemy;
class Player :
    public Animation
{

public:

    Player(Enemy* newEnemyPtr);
    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

    void SetCanAttack(bool newCanAttack);
    void SetHasAttacked(bool newHasAttacked);
    void JabAttack();
    void AttackCooldown();
    void OverhandAttack();

    bool CheckAlive();
    PlayerAttackBox GetPlayerAttackBox();


    void ChangeHealth(int damage);
    sf::Vector2f GetVelocity();

private:

    void UpdateAcceleration();

    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    sf::FloatRect attackArea;

    PlayerAttackBox attackBox;

    void LoadAnimation();
  
    void AttackCheck();

    bool canAttack;
    bool hasAttacked;
    int health;
    bool hasMovedRight;
    sf::Clock cooldownClock;
    sf::Time coolDownTimer;

    Enemy* enemyPtr;

    


};

