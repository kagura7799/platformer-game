#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.hpp"
#include "Sounds.hpp"

struct StateIdle
{
    std::string texturePath;
    int countFrames;
};

struct StateWalk
{
    std::string texturePath;
    std::string soundPath;
    int countFrames;
    bool loopSound;
};

struct StateShot
{
    std::string texturePath;
    std::string soundPath;
    int countFrames;
    bool loopSound;
};

struct PlayerStateInfo
{
    StateIdle idle;
    StateWalk walk;
    StateShot shot;
};

enum class PlayerState 
{
    Idle,
    WalkingLeft,
    WalkingRight,
    Shooting
};


class Player
{
public:
    Player(); 

    void handleInput();
    void update();
    void draw(sf::RenderWindow* window);

private:
    PlayerStateInfo stateInfo;

    void shot();
    void movement();
    void soundLoader();
    void setAnimation(int countFrames);
    void changeState(PlayerState newState, const std::string texturePath, int frameCount);

    Sounds soundManager;
    Animation playerAnimation;
    PlayerState currentState;

    sf::RectangleShape playerShape;
    sf::Texture playerTexture;
    sf::Clock clock;

    bool wasSpacePressed;
    bool isSpacePressed = false;
    bool spriteMirror;
    bool isWalkingSoundPlaying;
};

#endif
