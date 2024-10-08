#include <../include/GameManager.hpp>

void Game::initVariables() 
{
    this->window = nullptr;
}

void Game::initWindow() 
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->window = new sf::RenderWindow window(this->videoMode, "Ninja Negr");
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{                                                                               
    delete this->window;
}

void Game::update() 
{

}

void Game::render() 
{
    
}

