#include "Player.hpp"
#include "Game.hpp"

Player::Player()
{
    // hitBox - just a hitbox that will be used to track damage, collisions, etc. 

    // if (!texture.loadFromFile(path)) {
    //     std::cerr << "Could not load image" << std::endl;
    //     return false;
    // } 
    
    // sprite.setTexture(texture);
    hitBox.setSize(sf::Vector2f(70.f, 120.f));
    hitBox.setFillColor(sf::Color::Red);
    hitBox.setPosition(600, 400);
}

// player can move left and right, and he can jump
void Player::movement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) hitBox.move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) hitBox.move(1.f, 0.f);

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround) {
            isJumping = true;
            isOnGround = false;
            velocityY = jumpStrength; 
        }

        if (isJumping) 
        {
            velocityY += gravity; 
            hitBox.move(0, velocityY);

            if (hitBox.getPosition().y >= 500.0f) {
                hitBox.setPosition(hitBox.getPosition().x, 500.0f);
                isJumping = false;
                isOnGround = true;
                velocityY = 0.0f;
            }
        }
}

void Player::draw(sf::RenderWindow* window)
{
    window->draw(hitBox);
}