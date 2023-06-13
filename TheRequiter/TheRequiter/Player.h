#pragma once
#include "SpriteObject.h"
#include "Animation.h"

class Player :
    public Animation
{

public:

    Player();
    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;


    void ChangeHealth(int damage);
    sf::Vector2f GetVelocity();

private:

    void UpdateAcceleration();

    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    void LoadAnimation();
  
    sf::FloatRect AttackCheck();

    bool hasAttacked;
    int health;
    bool hasMovedRight;

protected:

    sf::Vector2f attackOffset;
    sf::Vector2f attackBoxScale;

    


};

