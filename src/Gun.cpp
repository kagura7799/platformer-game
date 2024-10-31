#include "Gun.hpp"

Gun::Gun() 
{
    ammo = 120;
    cartridgeClip = 30;
}

Bullet* Gun::createBullet(float bulletRadius, float bulletMovementSide, sf::Vector2f positionShoot, sf::Color bulletColor)
{
    Bullet* bullet = new Bullet{sf::CircleShape(), bulletMovementSide};

    bullet->bulletShape.setPosition(positionShoot.x + 140, positionShoot.y + 180);
    bullet->bulletShape.setRadius(bulletRadius);
    bullet->bulletShape.setFillColor(bulletColor);

    return bullet;
}

void Gun::updateBullet()
{   
    for (size_t i = 0; i < bullets.size();)
    {
        Bullet* bullet = bullets[i];

        // check if the bullet goes beyond the screen boundaries
        if (bullet->bulletShape.getPosition().x > 1400 || bullet->bulletShape.getPosition().x < -1000) 
        {
            delete bullet;
            bullets.erase(bullets.begin() + i);
        }

        else
        {
            bullet->bulletShape.move(bullet->movementSide, 0.f);
            ++i;
        }
    }
}

void Gun::shoot(bool playerSpriteMirror, float radius, sf::Vector2f positionShoot, sf::Color color)
{
    cartridgeClip--;
    std::cout << "в обойме при выстреле: " << cartridgeClip << std::endl;
    float side = playerSpriteMirror ? 5.0f : -5.0f;
    Bullet* createdBullet = createBullet(radius, side, positionShoot, color);
    bullets.push_back(createdBullet);
}

bool Gun::reload()
{
    if (cartridgeClip < 30 && ammo > 0)
    {
        int difference = (30 - cartridgeClip);
        
        if (ammo >= difference)
        {
            ammo -= difference;
            cartridgeClip += difference;
            return true;
        } else {
            cartridgeClip += ammo;
            ammo = 0;
            return true;
        }
    } else {
        std::cout << "reloading is impossible now" << std::endl;
        return false;
    }
}

void Gun::draw(sf::RenderWindow *window)
{
    for (Bullet* bullet : bullets)
    {
        window->draw(bullet->bulletShape);
    }
}

Gun::~Gun()
{
    for (Bullet* bullet : bullets)
    {
        delete bullet;
    }

    bullets.clear();
}
