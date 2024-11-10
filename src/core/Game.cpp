#include "Game.hpp"
#include <iostream>

void Game::initVariables()
{
    window = nullptr;
}

void Game::initWindow() 
{
    videoMode.height = 800;
    videoMode.width = 1400;

    // sf::Style::Fullscreen - once the game is completely ready add this

    window = new sf::RenderWindow(videoMode, "Zombie in city");
}

Game::Game()
{
    initVariables();
    initWindow();

    setBackground("Assets/Background/City2_pale.png");
}

Game::~Game()
{                                                                               
    delete window;
}

const bool Game::running() const
{
    return window->isOpen();
}

void Game::pollEvents()
{
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case ev.Closed:
            window->close();
            break;
        }
    }
}

bool Game::setBackground(std::string path) 
{
    backgroundTexture.loadFromFile(path);
    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        static_cast<float>(window->getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window->getSize().y) / backgroundTexture.getSize().y
    );

    return true;
}

void Game::update() 
{
    pollEvents();
    player.update();
    enemy.update();
}

void Game::render() 
{
    /*
        Renders the game object
        - clear old frame
        - render game objects
        - display frame in window
    */

    window->clear();
    window->draw(backgroundSprite);
    player.draw(window);
    enemy.draw(window);
    window->display();
}