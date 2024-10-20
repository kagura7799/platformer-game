#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Gun.hpp"

enum class PlayerState
{
    Idle,
    WalkingLeft,
    WalkingRight,
    Shooting
};

class Player
{
private:
    sf::Texture playerTexture;
    sf::Clock clock;

    Animation playerAnimation;
    Gun gun;
    PlayerState currentState;

    float gravity = 0.1f, jumpStrength = -8.0f, velocityY = 0.0f;
    bool isJumping = false, isOnGround = true, mirror = true;

    std::string pathToSprite;

    void changeState(PlayerState newState, const std::string& texturePath, int frameCount);
    void loadTextures();
    void handleInput();
    void setAnimation(int countFrames);
    void playAnimation(float deltaTime);

public:
    Player();

    int hp = 0, damage = 50, ammo = 15;
    sf::RectangleShape playerShape;
        
    void update();
    void draw(sf::RenderWindow *window);
};

#endif