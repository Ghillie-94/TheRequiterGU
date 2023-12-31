#pragma once
#include "Enemy.h"

class Player;
class Slim :
    public Enemy
{

public:

    Slim(sf::Vector2f newPosition, sf::Vector2f newPos1, sf::Vector2f newPos2, Player* newPlayerPtr, LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;

    void SetPosition(sf::Vector2f newPosition) override;

    void CheckHealth();

    void ChangeHealth(int damage) override;
    void AttackTimer() override;
    void DoAttack() override;

    void CheckDistance(Player* newPlayerPtr);

    
    void SetHasAttacked(bool newHasAttacked);

    void AttackCheck(Player& player) override;
    void SetCanAttack(bool newCanAttack);
    

    
    

    

private:

    void LoadAnimation();

    int health;
    
    bool hasAttacked;
    
    const float SPEED;
    const sf::Vector2f POS1;
    const sf::Vector2f POS2;
    sf::Vector2f playerPos;
    const sf::Vector2f* targetPoint;
    sf::Vector2f velocity;
    Player* playerPtr;
    sf::Clock cooldownClock;
    sf::Time cooldownTimer;
    sf::FloatRect attackArea;
 
};

