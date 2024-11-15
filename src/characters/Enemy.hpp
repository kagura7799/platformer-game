#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../effects/Animation.hpp"
#include "../effects/Sounds.hpp"
#include <SFML/Graphics.hpp>

struct EnemyShape
{
    sf::RectangleShape* enemyShape;
    bool spriteMirror;
    bool blockMove;
    int hp;
};

struct EnemyStateWalk
{
    std::string texturePath;
    std::string soundPath;
    int countFrames;
    bool loopSound;
};

struct EnemyStateAttack
{
    std::string texturePath;
    std::string soundPath;
    int countFrames;
    bool loopSound;
};

struct EnemyStateDead
{
    std::string texturePath;
    std::string soundPath;
    int countFrames;
    bool loopSound;
};

struct EnemyStateInfo
{
    EnemyStateAttack attack;
    EnemyStateWalk walk;
    EnemyStateDead dead;
};

enum class EnemyState
{
    Walk,
    Attack,
    Dead
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

private:
    int getRandomSpawnPosition();
    void soundLoader();
    void checkHp();
    void setAnimation(int countFrames);
    void movement();
    void changeState(EnemyState newState, const std::string texturePath, int frameCount);

    sf::Clock clock;
    sf::Texture enemyTexture;

    EnemyState currentState;
    EnemyStateInfo stateInfo;
    Animation enemyAnimation;
    Sounds soundManager;
};

#endif