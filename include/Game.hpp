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
    sf::VideoMode videoMode;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 
    bool isBackgroundSet = false; 
    
    void initVariables();
    void initWindow();

public:
    Game();
    virtual ~Game();

    const bool running() const;
    
    void setBackground(std::string image);
    void pollEvents(); 
    void render();
    void update();
};

#endif