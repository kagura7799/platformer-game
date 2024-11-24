#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../effects/Animation.hpp"
#include "../effects/Sounds.hpp"
#include <SFML/Graphics.hpp>

enum class EnemyState
{
    Walk,
    Attack,
    Dead
};

struct EnemyShape
{
    sf::RectangleShape* enemyShape;
    sf::Texture enemyTexture;
    EnemyState currentState;
    Animation enemyAnimation;

    bool spriteMirror;
    bool blockMove;
    bool isAlive;
    int hp;
};

class Enemy
{
public:
    Enemy();
    ~Enemy();

    std::vector<EnemyShape*> enemies;

    void spawn();
    void update();
    void draw(sf::RenderWindow* window);
    void checkHp(EnemyShape* enemy);

private:
    int getRandomSpawnPosition();
    void setAnimation(EnemyShape* enemy, int countFrames);
    void movement();
    void changeState(EnemyShape* enemyShape, EnemyState newState, const std::string texturePath, int frameCount);

    sf::Clock clock;
    Sounds soundManager;
};

#endif