#include <Game.hpp>
#include <iostream>

void Game::initVariables()
{
    window = nullptr;
}

void Game::initWindow() 
{
    videoMode.height = 800;
    videoMode.width = 1400;

    // sf::Style::Fullscreen

    window = new sf::RenderWindow(videoMode, "Ninja Negr");
}

Game::Game()
{
    initVariables();
    initWindow();
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

void Game::setBackground(std::string path) 
{
    if (!backgroundTexture.loadFromFile("/home/kagura/cpp/platformer-game/images/battleground-1.png")) {
        std::cerr << "Could not load image\n";
        return;
    }

    backgroundSprite.setTexture(backgroundTexture);

    backgroundSprite.setScale(
        static_cast<float>(window->getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window->getSize().y) / backgroundTexture.getSize().y
    );

    isBackgroundSet = true;    
}

void Game::update() 
{
    pollEvents();
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

    if (isBackgroundSet) 
    {
        window->draw(backgroundSprite);
    }

    window->display();
}