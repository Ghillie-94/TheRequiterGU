#pragma once
#include "Enemy.h"
class Slim :
    public Enemy
{

public:

    Slim(sf::Vector2f newPosition, sf::Vector2f newPos1, sf::Vector2f newPos2, Player* newPlayerPtr);

    void Update(sf::Time frameTime) override;

    void SetPosition(sf::Vector2f newPosition) override;

    void CheckHealth();

    void ChangeHealth(int damage) override;
    void CheckDistance(Player* newPlayerPtr);

    void SetCanAttack(bool newCanAttack);
    void SetHasAttacked(bool newHasAttacked);
    

    void CheckRange(Player* newPlayerPtr);

private:

    int health;
    bool canAttack;
    bool hasAttacked;
    bool playerInRange;
    const float SPEED;
    const sf::Vector2f POS1;
    const sf::Vector2f POS2;
    sf::Vector2f playerPos;
    const sf::Vector2f* targetPoint;
    sf::Vector2f velocity;
    Player* playerPtr;
};

