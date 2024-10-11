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

    // sf::Style::Fullscreen - once the game is completely ready add this

    window = new sf::RenderWindow(videoMode, "Ninja Negr");
}

Game::Game()
{
    sound.playBackgroundMusic();
    initVariables();
    initWindow();

    setBackground("/home/kagura/cpp/platformer-game/images/battleground-1.png");
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
    if (!backgroundTexture.loadFromFile(path)) {
        std::cerr << "Could not load image" << std::endl;
        return false;
    } 
    
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

    window->display();
}