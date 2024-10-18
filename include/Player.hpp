#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Gun.hpp"

class Player
{
private:
    sf::Texture playerTexture;
    sf::Clock clock;

    Animation playerAnimation;

    float gravity = 0.1f, jumpStrength = -8.0f, velocityY = 0.0f;
    bool isJumping = false, isOnGround = true, mirror = true;

    std::string pathToSprite;

public:
    Player();

    int hp = 100, damage = 50, ammo = 15;
    sf::RectangleShape playerShape;
        
    void update();
    void movement();
    void draw(sf::RenderWindow *window);
};

#endif