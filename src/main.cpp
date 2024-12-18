#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "core/Game.hpp"

int main()
{
    Game game;

    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;
}