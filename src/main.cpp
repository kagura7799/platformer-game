#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../include/GameManager.hpp"

int main()
{
    Game game();
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "Ninja Negr");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            gameLoop();
        }
    }

    return 0;
}