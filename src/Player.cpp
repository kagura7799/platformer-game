#include "Player.hpp"
#include <iostream>

Player::Player()    
{
    currentState = PlayerState::Idle;
    playerTexture.loadFromFile("Assets/images/sprites/Idle.png");

    playerShape.setTexture(&playerTexture);
    playerShape.setSize(sf::Vector2f(250, 250));
    playerShape.setPosition(450, 450);
    setAnimation(7);
}

void Player::setAnimation(int countFrames)
{
    playerAnimation.initTexture(&playerTexture, sf::Vector2u(countFrames, 1), 0.3f);
}

void Player::changeState(PlayerState newState, const std::string& texturePath, int frameCount)
{
    if (currentState != newState)
    {
        playerTexture.loadFromFile(texturePath);
        setAnimation(frameCount);
        currentState = newState;
    }
}

void Player::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        changeState(PlayerState::Shooting, "Assets/images/sprites/Shot_1.png", 4);
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
    {
        changeState(PlayerState::WalkingLeft, "Assets/images/sprites/Walk.png", 7);
        mirror = false;
        playerShape.move(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
    {
        changeState(PlayerState::WalkingRight, "Assets/images/sprites/Walk.png", 7);
        mirror = true;
        playerShape.move(1.f, 0.f);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
    {
        changeState(PlayerState::Idle, "Assets/images/sprites/Idle.png", 7);
    }
}

void Player::update()
{
    float deltaTime = clock.restart().asSeconds();

    handleInput();
    playerAnimation.Update(deltaTime, mirror);
    playerShape.setTextureRect(playerAnimation.uvRect);
}

void Player::draw(sf::RenderWindow* window)
{
    window->draw(playerShape);
}
