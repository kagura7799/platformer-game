#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../include/Game.hpp"

int main()
{
    Game game;

    game.setBackground("../images/battleground-1.png");

    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}