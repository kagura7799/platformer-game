#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Animation.hpp"
#include "Gun.hpp"
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

struct StateRecharge
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
    StateRecharge recharge;
};

enum class PlayerState 
{
    Idle,
    WalkingLeft,
    WalkingRight,
    Shooting,
    Recharging
};

class Player
{
public:
    Player(); 

    void handleInput();
    void update();
    void draw(sf::RenderWindow* window);

private:
    void shot();
    void movement();
    void startReload();
    void updateReload(float deltaTime);
    void completeReload();
    void recharge();
    void soundLoader();
    void setAnimation(int countFrames);
    void changeState(PlayerState newState, const std::string texturePath, int frameCount);
    bool checkSwitchAnimation(PlayerState currentState);

    Gun gun;
    PlayerStateInfo stateInfo;
    PlayerState currentState;
    Animation playerAnimation;
    Sounds soundManager;

    sf::Clock clock;
    sf::RectangleShape playerShape;
    sf::Texture playerTexture;

    float reloadTimer;

    bool KEY_A;
    bool KEY_D;
    bool KEY_R;
    bool KEY_SPACE;

    bool isRechargingAnimationComplete;
    bool reloadingIsEnd;
    bool isReloadingButton;
    bool wasReloadingButton;
    bool wasSpacePressed;
    bool isSpacePressed;
    bool spriteMirror;
    bool isWalkingSoundPlaying;
};

#endif
