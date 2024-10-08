#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game 
{
private:
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode = videoMode;

    int initVariables();
    int initWindow();

public:
    Game();
    virtual ~Game();

    void render();
    void update();
}

#endif