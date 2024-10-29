#include "Gun.hpp"

Bullet* Gun::createBullet(float bulletRadius, float bulletMovementSide, sf::Vector2f positionShoot, sf::Color bulletColor)
{
    Bullet* bullet = new Bullet{sf::CircleShape(), bulletMovementSide};

    bullet->bulletShape.setPosition(positionShoot.x + 140, positionShoot.y + 180);
    bullet->bulletShape.setRadius(bulletRadius);
    bullet->bulletShape.setFillColor(bulletColor);

    return bullet;
}

void Gun::shoot(bool playerSpriteMirror, float radius, sf::Vector2f positionShoot, sf::Color color)
{
    float side = playerSpriteMirror ? 5.0f : -5.0f;
    Bullet* createdBullet = createBullet(radius, side, positionShoot, color);
    bullets.push_back(createdBullet);
}

void Gun::updateBullet()
{
    for (Bullet* bullet : bullets)
    {
        bullet->bulletShape.move(bullet->movementSide, 0.f);
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
