#include "Player.hpp"

Player::Player()    
{
    stateInfo.idle = {"Assets/Player/sprites/Idle.png", 7};
    stateInfo.walk = {"Assets/Player/sprites/Walk.png", "Assets/Player/sounds/walk.ogg", 7, false};
    stateInfo.shot = {"Assets/Player/sprites/Shot_1.png", "Assets/Player/sounds/shot.ogg", 4, false};
    stateInfo.recharge = {"Assets/Player/sprites/Recharge.png", "Assets/Player/sounds/recharge.ogg", 13, false};

    soundLoader();
    
    currentState = PlayerState::Idle;
    playerTexture.loadFromFile(stateInfo.idle.texturePath);
    setAnimation(stateInfo.idle.countFrames);

    playerShape.setTexture(&playerTexture);
    playerShape.setSize(sf::Vector2f(250, 250));
    playerShape.setPosition(450, 450);    

    reloadTimer = 0.0f;
}

void Player::soundLoader()
{
    soundManager.loadSound("walk", stateInfo.walk.soundPath, stateInfo.walk.loopSound);
    soundManager.loadSound("shot", stateInfo.shot.soundPath, stateInfo.shot.loopSound);
    soundManager.loadSound("recharge", stateInfo.recharge.soundPath, stateInfo.recharge.loopSound);
    soundManager.loadSound("no-ammo", "Assets/Player/sounds/no-ammo.ogg", false);
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
    isSpacePressed = KEY_SPACE;
    sf::Vector2f playerPos = playerShape.getPosition();

    if (isSpacePressed && !wasSpacePressed) 
    {
        if (gun.cartridgeClip > 0)
        {
            gun.shoot(spriteMirror, 2.f, playerPos, sf::Color::Yellow);
            changeState(PlayerState::Shooting, stateInfo.shot.texturePath, stateInfo.shot.countFrames);
            soundManager.playSound("shot");
        } else {
            soundManager.playSound("no-ammo");
        }

        soundManager.stopSound("recharge");
        reloadingIsEnd = true;

        if (soundManager.isSoundPlaying("walk")) soundManager.stopSound("walk");
        wasSpacePressed = true;
    }   

    if (!isSpacePressed) wasSpacePressed = false;
}

void Player::startReload() 
{
    changeState(PlayerState::Recharging, stateInfo.recharge.texturePath, stateInfo.recharge.countFrames);
    soundManager.playSound("recharge");
    reloadingIsEnd = false;
    reloadTimer = 2.0f;
}

void Player::updateReload(float deltaTime) 
{
    if (reloadTimer > 0.0f) {
        reloadTimer -= deltaTime;

        if (reloadTimer <= 0.0f) {
            completeReload();
        }
    }
}

void Player::completeReload() 
{
    // if player starting to walk or shooting and etc before complete reload - do not give ammo
    if (currentState == PlayerState::Recharging)
    {
        int difference = (30 - gun.cartridgeClip);
        if (gun.ammo >= difference) {
            gun.ammo -= difference;
            gun.cartridgeClip += difference;
        } else {
            gun.cartridgeClip += gun.ammo;
            gun.ammo = 0;
        }
        reloadingIsEnd = true;

        std::cout << "completeReload" << std::endl;
        std::cout << "ammo: " << gun.cartridgeClip << std::endl;
    }
}

void Player::recharge() 
{
    isReloadingButton = KEY_R;
    if (isReloadingButton && !wasReloadingButton && reloadingIsEnd) {
        if (gun.cartridgeClip < 30 && gun.ammo > 0) {
            startReload();
        } else {
            std::cout << "reloading is impossible now" << std::endl;
        }
        wasReloadingButton = true;
    }
    if (!isReloadingButton) wasReloadingButton = false;
}

void Player::damageToEnemy() 
{
    for (EnemyShape* enemy : enemy.enemies) {
        for (auto bulletIt = gun.bullets.begin(); bulletIt != gun.bullets.end();) {
            Bullet* bullet = *bulletIt;

            if (bullet->bulletShape.getGlobalBounds().intersects(enemy->enemyShape->getGlobalBounds())) {
                enemy->hp -= 20;
                delete bullet;
                bulletIt = gun.bullets.erase(bulletIt);
            } else {
                ++bulletIt;
            }
        }
    }
}

void Player::movement()
{
    // stop recharging when player start walk
    if (KEY_A || KEY_D)
    {
        reloadingIsEnd = true;
        soundManager.stopSound("recharge");
    }

    // used checking space and R pressed, to avoid bug
    if (!isSpacePressed && reloadingIsEnd)
    {
        if (KEY_A && KEY_D)
        {
            changeState(PlayerState::Idle, stateInfo.idle.texturePath, stateInfo.idle.countFrames);
            soundManager.stopSound("walk");
            soundManager.stopSound("shot");
            return;
        }
        
        if (KEY_A && !KEY_D)
        {
            changeState(PlayerState::WalkingLeft, stateInfo.walk.texturePath, stateInfo.walk.countFrames);
            if (!soundManager.isSoundPlaying("walk")) soundManager.playSound("walk");
            spriteMirror = false;
            playerShape.move(-0.5f, 0.f);
        }

        else if (KEY_D && !KEY_A)
        {
            changeState(PlayerState::WalkingRight, stateInfo.walk.texturePath, stateInfo.walk.countFrames);
            if (!soundManager.isSoundPlaying("walk")) soundManager.playSound("walk");
            spriteMirror = true;
            playerShape.move(0.5f, 0.f);
        }

        else
        {
            if (!wasSpacePressed) changeState(PlayerState::Idle, stateInfo.idle.texturePath, stateInfo.idle.countFrames);
            soundManager.stopSound("walk");
        }
    }
}

void Player::handleInput()
{
    shot(); 
    movement();
    recharge();
}

void Player::update()
{
    KEY_A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    KEY_D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    KEY_R = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    KEY_SPACE = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    float deltaTime = clock.restart().asSeconds();

    handleInput();
    gun.updateBullet();
    enemy.update();

    damageToEnemy();
    updateReload(deltaTime);

    if (currentState == PlayerState::Recharging && playerAnimation.isAnimationComplete())
    {
        reloadingIsEnd = true;
    }

    playerAnimation.Update(deltaTime, spriteMirror);
    playerShape.setTextureRect(playerAnimation.uvRect);
}

void Player::draw(sf::RenderWindow *window)
{
    window->draw(playerShape);
    gun.draw(window);
    enemy.draw(window);
}