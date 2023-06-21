#pragma once
#include "SpriteObject.h"
#include "Animation.h"



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
    


    void ChangeHealth(int damage);
    sf::Vector2f GetVelocity();
    void AttackCheck(Enemy& other);

private:

    void UpdateAcceleration();

    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    sf::FloatRect attackArea;

    

    void LoadAnimation();
  
    

    bool canAttack;
    bool hasAttacked;
    int health;
    bool hasMovedRight;
    sf::Clock cooldownClock;
    sf::Time coolDownTimer;

    Enemy* enemyPtr;

    


};

