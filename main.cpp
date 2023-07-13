#include <SFML/Graphics.hpp>
#include "player.cpp"
#include <iostream>
#include <vector>

// Todas las funciones y clases que veas escritas aqui son puro placeholder para entender las funcionalidades de SFML, la mayoría será re-hecha
// con técnicas más eficientes, pues por ahora parece que un niño de 7 años con autismo hubiera escrito el código




int main()
{

    // Creación de la pantalla
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Outcast Game is going Bitches");
    window.setFramerateLimit(60);


    // Carga del spritesheet
    sf::Texture spritesheet_pj;
    if (!spritesheet_pj.loadFromFile("images/spritesheet.png"))
        std::cout << "Error loading texture" << std::endl;

    Player player(&spritesheet_pj); //Inicializacion player

    float deltaTime = 0.0f;
    sf::Clock clock;

    sf::Event event;

    while (window.isOpen())
    {

        deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(deltaTime);
        window.clear();
        window.draw(player);
        window.display();
    }
}