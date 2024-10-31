#ifndef GUN_HPP
#define GUN_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

struct Bullet
{
    sf::CircleShape bulletShape;
    const float movementSide;
};

class Gun
{
private:
    std::vector<Bullet*> bullets; 
    Bullet* createBullet(float bulletRadius, const float bulletMovementSide, sf::Vector2f positionShoot, sf::Color bulletColor);

public:
    int ammo;
    int cartridgeClip;

    void shoot(bool playerSpriteMirror, float radius, sf::Vector2f positionShoot, sf::Color color);
    bool reload();
    void updateBullet();
    void draw(sf::RenderWindow *window);

    Gun();
    ~Gun();
};

#endif