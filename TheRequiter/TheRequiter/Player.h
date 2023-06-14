#pragma once
#include "SpriteObject.h"
#include "Animation.h"
#include "PlayerAttackBox.h"

class Player :
    public Animation
{

public:

    Player();
    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;

    void SetCanAttack(bool newCanAttack);
    void SetHasAttacked(bool newHasAttacked);
    void JabAttack();
    void OverhandAttack();

    void ChangeHealth(int damage);
    sf::Vector2f GetVelocity();

private:

    void UpdateAcceleration();

    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    PlayerAttackBox attackBox;

    void LoadAnimation();
  
    void AttackCheck();

    bool canAttack;
    bool hasAttacked;
    int health;
    bool hasMovedRight;



    


};

