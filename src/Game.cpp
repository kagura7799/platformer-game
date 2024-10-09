#include <Game.hpp>

void Game::initVariables() 
{
    window = nullptr;
}

void Game::initWindow() 
{
    videoMode.height = 600;
    videoMode.width = 800;
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

void Game::update() 
{
    pollEvents();
}

void Game::render() 
{
    /*
        Renders the game objectd
        - clear old frame
        - render game objects
        - display frame in window
    */
   
    window->clear(sf::Color(255, 0, 0, 255));

    window->display();
}

