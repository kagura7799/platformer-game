#include "Enemy.hpp"
#include <vector>
#include <random>
#include <iostream>

Enemy::Enemy()
{
    // stateInfo.attack = {}; // TODO: implement structure 
    // stateInfo.walk = {};

    soundLoader();
    spawn();

    currentState = EnemyState::Walk;
    enemyTexture.loadFromFile("Assets/Enemy/Wild-Zombie/sprites/Walk.png");
    setAnimation(10);
}

int Enemy::getRandomSpawnPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1,2);

    return dist(gen);
}

void Enemy::soundLoader()
{
    
}

void Enemy::setAnimation(int countFrames)
{
    enemyAnimation.initTexture(&enemyTexture, sf::Vector2u(countFrames, 1), 0.3f);
}

void Enemy::changeState(EnemyState newState, const std::string texturePath, int frameCount)
{
    if (currentState != newState)
    {
        enemyTexture.loadFromFile(texturePath);
        setAnimation(frameCount);
        currentState = newState;
    }
}

void Enemy::spawn()
{
    sf::RectangleShape* enemyShape = new sf::RectangleShape;
    enemyShape->setTexture(&enemyTexture);
    enemyShape->setSize(sf::Vector2f(230, 230));

    EnemyShape enemy;
    enemy.enemyShape = enemyShape;
    enemy.hp = 100;
    enemy.blockMove = false;

    // random define side where the enemy will be spawned
    if (getRandomSpawnPosition() == 1) 
    {
        enemy.enemyShape->setPosition(1, 468);
        enemy.spriteMirror = true;
    } else {
        enemy.enemyShape->setPosition(1300, 468);
        enemy.spriteMirror = false;
    }

    enemies.push_back(new EnemyShape(enemy));
}

void Enemy::checkHp()
{
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
    {
        EnemyShape* enemy = *enemyIt;

        if (enemy->hp <= 0)
        {
            enemy->blockMove = true;
            if (currentState != EnemyState::Dead) {
                changeState(EnemyState::Dead, "Assets/Enemy/Wild-Zombie/sprites/Dead.png", 5);
            }

            if (enemyAnimation.isAnimationComplete())
            {
                delete enemy;
                enemyIt = enemies.erase(enemyIt);
            } else {
                ++enemyIt;
            }
        }
        else {
            ++enemyIt;
        }
    }
}

void Enemy::movement()
{
    for (EnemyShape* enemy : enemies)
    {
        if (!enemy->blockMove)
        {
            if (enemy->spriteMirror) {
                enemy->enemyShape->move(0.3f, 0.f);
            } else {
            enemy->enemyShape->move(-0.3f, 0.f);
            }
        }
    }
}

void Enemy::update()
{
    float deltaTime = clock.restart().asSeconds();

    for (EnemyShape* enemy : enemies)
    {
        enemyAnimation.Update(deltaTime, enemy->spriteMirror);
        enemy->enemyShape->setTextureRect(enemyAnimation.uvRect);
    }

    checkHp();
    movement();
}

void Enemy::draw(sf::RenderWindow* window)
{
    for (EnemyShape* enemy : enemies)
    {
        window->draw(*enemy->enemyShape);
    }
}

Enemy::~Enemy()
{
    for (EnemyShape* enemy : enemies)
    {
        delete enemy->enemyShape;
        delete enemy;
    }

    enemies.clear();
}