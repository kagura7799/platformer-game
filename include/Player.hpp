#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Sounds.hpp"

enum class PlayerState {
    Idle,
    WalkingLeft,
    WalkingRight,
    Shooting
};

class Player {
public:
    Player(); 

    void handleInput();
    void update();
    void draw(sf::RenderWindow* window);

private:
    const std::string idleSprite = "Assets/images/sprites/Idle.png";
    const std::string walkSprite = "Assets/images/sprites/Walk.png";
    const std::string shotSprite = "Assets/images/sprites/Shot_1.png";

    void shot();
    void movement();
    void soundLoader();
    void setAnimation(int countFrames);
    void changeState(PlayerState newState, const std::string& texturePath, int frameCount);

    Sounds soundManager;
    Animation playerAnimation;
    PlayerState currentState;

    sf::RectangleShape playerShape;
    sf::Texture playerTexture;
    sf::Clock clock;

    bool wasSpacePressed;
    bool isSpacePressed = false;
    bool mirror;
    bool isWalkingSoundPlaying;
};

#endif
