#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Sounds.hpp"

class Game 
{
private:
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 
    
    void initVariables();
    void initWindow();

public:
    Game();
    virtual ~Game();

    Sounds sound;

    const bool running() const;
    void pollEvents(); 
    void render();
    void update();

    bool setBackground(std::string path);
};

#endif