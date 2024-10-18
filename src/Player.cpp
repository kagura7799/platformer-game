#include "Player.hpp"
#include <iostream>

Player::Player()    
{
    playerTexture.loadFromFile("/home/kagura/cpp/platformer-game/Assets/images/sprites/Idle.png");

    int frameWidth = playerTexture.getSize().x / 7;
    int frameHeight = playerTexture.getSize().y / 1;

    playerAnimation.initTexture(&playerTexture, sf::Vector2u(7, 1), 0.3f);
    playerShape.setTexture(&playerTexture);
    playerShape.setSize(sf::Vector2f(frameWidth, frameHeight));
    playerShape.setPosition(600, 600);
}

// player can move left and right, and he can jump
void Player::movement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
    {
        playerTexture.loadFromFile("/home/kagura/cpp/platformer-game/Assets/images/sprites/Walk.png");
        mirror = false;
        playerShape.move(-1.f, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
    {
        playerTexture.loadFromFile("/home/kagura/cpp/platformer-game/Assets/images/sprites/Walk.png");
        mirror = true;
        playerShape.move(1.f, 0.f);
    }

    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        // shoot();
    }
}

void Player::update()
{
    float deltaTime = clock.restart().asSeconds();
    playerTexture.loadFromFile("/home/kagura/cpp/platformer-game/Assets/images/sprites/Idle.png"); // reset default state (idle)
    
    movement();
    playerAnimation.Update(deltaTime, mirror);
    playerShape.setTextureRect(playerAnimation.uvRect);
}

void Player::draw(sf::RenderWindow* window)
{
    window->draw(playerShape);
}
