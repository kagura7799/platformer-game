#include "Enemy.hpp"
#include <vector>
#include <random>
#include <iostream>

Enemy::Enemy()
{
    spawn();
    spawn();
}

int Enemy::getRandomSpawnPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1,2);

    return dist(gen);
}

void Enemy::setAnimation(EnemyShape* enemy, int countFrames)
{
    enemy->enemyAnimation.initTexture(&enemy->enemyTexture, sf::Vector2u(countFrames, 1), 0.3f);
}

void Enemy::changeState(EnemyShape* enemy, EnemyState newState, const std::string texturePath, int frameCount)
{
    if (enemy->currentState != newState)
    {
        enemy->enemyTexture.loadFromFile(texturePath);
        setAnimation(enemy, frameCount);
        enemy->currentState = newState;
    }
}

void Enemy::spawn()
{
    sf::RectangleShape* enemyShape = new sf::RectangleShape;
    EnemyShape* enemy = new EnemyShape;

    enemy->enemyShape = enemyShape;
    enemy->currentState = EnemyState::Walk;
    enemy->hp = 100;
    enemy->blockMove = false;
    enemy->isAlive = true;

    enemy->enemyTexture.loadFromFile("Assets/Enemy/Wild-Zombie/sprites/Walk.png");
    setAnimation(enemy, 10);
    enemyShape->setTexture(&enemy->enemyTexture);
    enemyShape->setSize(sf::Vector2f(230, 230));

    // random define side where the enemy will be spawned
    if (getRandomSpawnPosition() == 1) 
    {
        enemy->enemyShape->setPosition(1, 468);
        enemy->spriteMirror = true;
    } else {
        enemy->enemyShape->setPosition(1300, 468);
        enemy->spriteMirror = false;
    }

    enemies.push_back(enemy);
}

void Enemy::checkHp(EnemyShape* enemy)
{
    if (enemy->hp <= 0 && enemy->isAlive)
    {   
        enemy->isAlive = false;
        enemy->blockMove = true;

        if (enemy->currentState != EnemyState::Dead) 
            changeState(enemy, EnemyState::Dead, "Assets/Enemy/Wild-Zombie/sprites/Dead.png", 5);

        if (enemy->enemyAnimation.isAnimationComplete())
        {
            auto it = std::find(enemies.begin(), enemies.end(), enemy);
            if (it != enemies.end()) {
                delete enemy; 
                enemies.erase(it); 
            }
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
        enemy->enemyAnimation.Update(deltaTime, enemy->spriteMirror);
        enemy->enemyShape->setTextureRect(enemy->enemyAnimation.uvRect);
    }

    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        EnemyShape* enemy = *it;

        if (enemy->currentState == EnemyState::Dead && enemy->enemyAnimation.isAnimationComplete())
        {
            delete enemy;
            it = enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }

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