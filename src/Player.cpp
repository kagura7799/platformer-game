#include "Player.hpp"

Player::Player()    
{
    stateInfo.idle = {"Assets/images/sprites/Idle.png", 7};
    stateInfo.walk = {"Assets/images/sprites/Walk.png", "Assets/sounds/walk.ogg", 7, false};
    stateInfo.shot = {"Assets/images/sprites/Shot_1.png", "Assets/sounds/shot.ogg", 4, false};

    soundLoader();
    
    currentState = PlayerState::Idle;
    playerTexture.loadFromFile(stateInfo.idle.texturePath);
    setAnimation(stateInfo.idle.countFrames);

    playerShape.setTexture(&playerTexture);
    playerShape.setSize(sf::Vector2f(250, 250));
    playerShape.setPosition(450, 450);    
}

void Player::soundLoader()
{
    soundManager.loadSound("walk", stateInfo.walk.soundPath, stateInfo.walk.loopSound);
    soundManager.loadSound("shot", stateInfo.shot.soundPath, stateInfo.shot.loopSound);
}

void Player::setAnimation(int countFrames)
{
    playerAnimation.initTexture(&playerTexture, sf::Vector2u(countFrames, 1), 0.3f);
}

void Player::changeState(PlayerState newState, const std::string texturePath, int frameCount)
{
    if (currentState != newState)
    {
        playerTexture.loadFromFile(texturePath);
        setAnimation(frameCount);
        currentState = newState;
    }
}

void Player::shot()
{
    isSpacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gun.cartridgeClip > 0;
    sf::Vector2f playerPos = playerShape.getPosition();

    if (isSpacePressed && !wasSpacePressed) 
    {
        gun.shoot(spriteMirror, 2.f, playerPos, sf::Color::Yellow);
        changeState(PlayerState::Shooting, stateInfo.shot.texturePath, stateInfo.shot.countFrames);

        if (soundManager.isSoundPlaying("walk")) soundManager.stopSound("walk");
        soundManager.playSound("shot");
        wasSpacePressed = true;
    }

    if (!isSpacePressed) wasSpacePressed = false;
}

void Player::reload()
{
    isReloadingButton = sf::Keyboard::isKeyPressed(sf::Keyboard::R);

    if (isReloadingButton && !wasReloadingButton)
    {
        if (gun.reload()) 
        {
            // TODO: play animation and sound reload
        }
        wasReloadingButton = true;
    }

    if (!isReloadingButton) wasReloadingButton = false;
}

void Player::movement()
{
    // used checking space pressed, to avoid bug with pressed button A or D and button Space

    if (!isSpacePressed && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        changeState(PlayerState::Idle, stateInfo.idle.texturePath, stateInfo.idle.countFrames);
        soundManager.stopSound("walk");
        soundManager.stopSound("shot");
        return;
    }

    if (!isSpacePressed && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        changeState(PlayerState::WalkingLeft, stateInfo.walk.texturePath, stateInfo.walk.countFrames);
        if (!soundManager.isSoundPlaying("walk")) soundManager.playSound("walk");
        spriteMirror = false;
        playerShape.move(-1.f, 0.f);
    }

    else if (!isSpacePressed && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        changeState(PlayerState::WalkingRight, stateInfo.walk.texturePath, stateInfo.walk.countFrames);
        if (!soundManager.isSoundPlaying("walk")) soundManager.playSound("walk");
        spriteMirror = true;
        playerShape.move(1.f, 0.f);
    }

    else
    {
        if (!wasSpacePressed) changeState(PlayerState::Idle, stateInfo.idle.texturePath, stateInfo.idle.countFrames);
        soundManager.stopSound("walk");
    }
}

void Player::handleInput()
{
    shot();
    reload();
    movement();
}

void Player::update()
{
    float deltaTime = clock.restart().asSeconds();

    handleInput();
    gun.updateBullet();
    playerAnimation.Update(deltaTime, spriteMirror);
    playerShape.setTextureRect(playerAnimation.uvRect);
}

void Player::draw(sf::RenderWindow *window)
{
    window->draw(playerShape);
    gun.draw(window);
}