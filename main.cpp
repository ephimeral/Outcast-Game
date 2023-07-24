#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "src/game.h"
#include <iostream>

int main()
{
    std::cout << "hola" << std::endl;
    Game game;
    std::cout << "Game created" << std::endl;
    game.run();
}

