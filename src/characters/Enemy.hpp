#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../effects/Animation.hpp"
#include "../effects/Sounds.hpp"
#include <SFML/Graphics.hpp>

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

struct EnemyStateInfo
{
    EnemyStateAttack attack;
    EnemyStateWalk walk;
};

enum class EnemyState
{
    Walk,
    Attack
};

class Enemy
{
public:
    Enemy();
    sf::RectangleShape enemyShape;  

    void spawn();
    void update();
    void draw(sf::RenderWindow* window);

private:
    void soundLoader();
    void setAnimation(int countFrames);
    void movement();
    void changeState(EnemyState newState, const std::string texturePath, int frameCount);

    sf::Texture enemyTexture;

    EnemyState currentState;
    EnemyStateInfo stateInfo;
    Animation enemyAnimation;
    Sounds soundManager;
};

#endif