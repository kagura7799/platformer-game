#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::RectangleShape hitBox;
    
    sf::Texture texture;
    sf::Sprite sprite;

    float gravity = 0.1f, jumpStrength = -8.0f, velocityY = 0.0f;
    bool isJumping = false, isOnGround = true; 

public:
    Player();

    void movement();
    void draw(sf::RenderWindow* window);
};

#endif