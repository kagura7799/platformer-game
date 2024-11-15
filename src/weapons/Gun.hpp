#ifndef GUN_HPP
#define GUN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../effects/Animation.hpp"

struct Bullet
{
    sf::CircleShape bulletShape;
    const float movementSide;
};

class Gun
{
private:
    Animation playerAnimation;
    Bullet* createBullet(float bulletRadius, const float bulletMovementSide, sf::Vector2f positionShoot, sf::Color bulletColor);

public:
    int ammo;
    int cartridgeClip;

    std::vector<Bullet*> bullets; 
    
    void shoot(bool playerSpriteMirror, float radius, sf::Vector2f positionShoot, sf::Color color);
    void updateBullet();
    void draw(sf::RenderWindow *window);

    Gun();
    ~Gun();
};

#endif