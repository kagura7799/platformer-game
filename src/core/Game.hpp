#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "../effects/Sounds.hpp"
#include "../characters/Player.hpp"
#include "../characters/Enemy.hpp"

class Game 
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event ev;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 
    
    void initVariables();
    void initWindow();

public:
    Game();
    virtual ~Game();

    Sounds sounds;
    Player player;
    Enemy enemy;

    const bool running() const;
    void pollEvents(); 
    void render();
    void update();

    bool setBackground(std::string path);
};

#endif