#pragma once
#include "SpriteObject.h"
class Player :
    public SpriteObject
{

public:

    Player();
    void Update(sf::Time frameTime) override;
    void HandleCollision(SpriteObject& other) override;
    void AttackCheck();
    void ChangeHealth(int damage);
    sf::Vector2f GetVelocity();

private:

    void UpdateAcceleration();

    sf::Vector2f twoFramesOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    bool hasAttacked;
    int health;
    bool hasMovedRight;
};

