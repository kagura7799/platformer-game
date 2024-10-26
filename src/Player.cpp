#include "Player.hpp"
#include <iostream>

Player::Player()    
{
    soundLoader();
    
    currentState = PlayerState::Idle;
    playerTexture.loadFromFile("Assets/images/sprites/Idle.png");

    playerShape.setTexture(&playerTexture);
    playerShape.setSize(sf::Vector2f(250, 250));
    playerShape.setPosition(450, 450);
    setAnimation(7);
}

void Player::soundLoader()
{
    soundManager.loadSound("walk", "Assets/sounds/walk.ogg", false);
    soundManager.loadSound("shot", "Assets/sounds/shot.ogg", false);
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

void Player::shot()
{
    isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (isSpacePressed && !wasSpacePressed) 
    {
        changeState(PlayerState::Shooting, "shoot", 4);

        if (soundManager.isSoundPlaying("walk")) soundManager.stopSound("walk");
        soundManager.playSound("shot");
        wasSpacePressed = true;
    }

    if (!isSpacePressed) 
    {
        wasSpacePressed = false;
    }
}

void Player::movement()
{
    if (!(isSpacePressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
    {
        changeState(PlayerState::Idle, idleSprite, 7);
        soundManager.stopSound("walk");
        soundManager.stopSound("shot");
        return;
    }

    if ((!isSpacePressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))) 
    {
        changeState(PlayerState::WalkingLeft, walkSprite, 7);
        if (!soundManager.isSoundPlaying("walk")) soundManager.playSound("walk");
        mirror = false;
        playerShape.move(-1.f, 0.f);
    }

    else if ((!isSpacePressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))) 
    {
        changeState(PlayerState::WalkingRight, walkSprite, 7);
        if (!soundManager.isSoundPlaying("walk")) soundManager.playSound("walk");
        mirror = true;
        playerShape.move(1.f, 0.f);
    }

    else
    {
        if (!wasSpacePressed) changeState(PlayerState::Idle, idleSprite, 7);
        soundManager.stopSound("walk");
    }
}

void Player::handleInput()
{
    shot();
    movement();
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