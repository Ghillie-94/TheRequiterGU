#pragma once
#include "Enemy.h"
class Slim :
    public Enemy
{

public:

    Slim(sf::Vector2f newPosition, sf::Vector2f newPos1, sf::Vector2f newPos2);

    void Update(sf::Time frameTime) override;

    void SetPosition(sf::Vector2f newPosition) override;

    void CheckHealth();

    void ChangeHealth(int damage);

    void SetCanAttack(bool newCanAttack);
    void SetHasAttacked(bool newHasAttacked);

private:

    int health;
    bool canAttack;
    bool hasAttacked;
    const float SPEED;
    const sf::Vector2f POS1;
    const sf::Vector2f POS2;
    sf::Vector2f playerPos;
    const sf::Vector2f* targetPoint;
    sf::Vector2f velocity;
};

