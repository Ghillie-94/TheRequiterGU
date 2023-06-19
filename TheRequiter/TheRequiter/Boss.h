#pragma once
#include "Enemy.h"
#include "EnemyAttackBox.h"
#include "LevelScreen.h"

class Player;
class Boss :
    public Enemy
{
public:

    Boss(sf::Vector2f newPosition, sf::Vector2f newPos1, sf::Vector2f newPos2, Player* newPlayerPtr, LevelScreen* newLevelScreen);

    void Update(sf::Time frameTime) override;

    void SetPosition(sf::Vector2f newPosition) override;

    void CheckHealth();

    void ChangeHealth(int damage) override;
    void AttackTimer() override;
    void DoAttack() override;
    void AttackCheck(bool newCanAttack) override;
    void CheckDistance(Player* newPlayerPtr);

    
    void SetHasAttacked(bool newHasAttacked);

    


    

private:

    void LoadAnimation();

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
    sf::Clock cooldownClock;
    sf::Time cooldownTimer;
    EnemyAttackBox bossAttackBox;
    LevelScreen* levelScreen;

};

