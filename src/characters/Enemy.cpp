#include "Enemy.hpp"

Enemy::Enemy()
{
    // stateInfo.attack = {}; // TODO: implement structure 
    // stateInfo.walk = {};

    soundLoader();
    spawn();

    currentState = EnemyState::Walk;
    enemyTexture.loadFromFile("Assets/images/sprites/Enemy/Wild-Zombie/Walk.png");
    setAnimation(10);

    enemyShape.setTexture(&enemyTexture);
    enemyShape.setSize(sf::Vector2f(250, 250));
    enemyShape.setPosition(400, 450);
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

}

void Enemy::spawn()
{
    
}

void Enemy::movement()
{
    
}

void Enemy::update()
{
    movement();
}

void Enemy::draw(sf::RenderWindow* window)
{
    window->draw(enemyShape);
}