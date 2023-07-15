#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "player.cpp"
#include "collider.h"
#include <iostream>
#include <vector>

// Todas las funciones y clases que veas escritas aqui son puro placeholder para entender las funcionalidades de SFML, la mayoría será re-hecha
// con técnicas más eficientes, pues por ahora parece que un niño de 7 años con autismo hubiera escrito el código

bool checkCollision(sf::RectangleShape& shape1, sf::RectangleShape& shape2) {
  sf::FloatRect boundingBox1 = shape1.getGlobalBounds();
  sf::FloatRect boundingBox2 = shape2.getGlobalBounds();

  return boundingBox1.intersects(boundingBox2);
}

int main()
{

    // Creación de la pantalla
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Outcast Game is going Bitches");
    window.setFramerateLimit(60);


    // Carga del spritesheet
    sf::Texture spritesheet_pj;
    if (!spritesheet_pj.loadFromFile("images/spritesheet.png"))
        std::cout << "Error loading texture" << std::endl;

    sf::Texture wall_texture;
    if (!wall_texture.loadFromFile("images/wall.png"))
        std::cout << "Error loading texture" << std::endl;
    Player player(&spritesheet_pj); //Inicializacion player

    class Wall : public sf::Drawable
    {
    public:
        sf::RectangleShape body;
    public:
        Wall(){
        body.setPosition(120, 200);
        body.setFillColor(sf::Color::Green);
        body.setSize(sf::Vector2f(1000, 50));
    }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(body);
        }

        Collider getCollider() {return Collider(body);}
    };

    Wall wall;

    // Crear un rectángulo (hitbox) en función de las dimensiones del sprite


    // Vincular el rectángulo a la posición del sprite

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


        //CODIGO DE MIERDA PERO FUNCIONA, REFACTORIZA ESTA CAGADA Y PIENSA EN COMO INTRODUCIRÁS EL SISTEMA

        //LAS COLISIONES DEBEN EJECUTARSE ->ANTES<- DE CUALQUIER ACTUALIZACIÓN DE MOVIMIENTO setPosition() EN UPDATE

        if (checkCollision(player.FeetHitbox, wall.body))
        {
            // Variables de tamaño y posición de las hitboxes y sprites
            sf::Vector2f shape1Position = player.FeetHitbox.getPosition();
            sf::Vector2f shape2Position = wall.body.getPosition();
            sf::Vector2f shape1Size = player.FeetHitbox.getSize();
            sf::FloatRect boundingBox1 = player.FeetHitbox.getGlobalBounds();
            sf::FloatRect boundingBox2 = wall.body.getGlobalBounds();
            sf::Vector2f spriteSize = player.SpriteHitbox.getSize();
            sf::Vector2f shape2Size = wall.body.getSize();

            double offsetX = (boundingBox1.left + boundingBox1.width / 2.0) - (boundingBox2.left + boundingBox2.width / 2.0);
            double offsetY = (boundingBox1.top + boundingBox1.height / 2.0) - (boundingBox2.top + boundingBox2.height / 2.0);

            double intersectX = abs(offsetX) - (shape1Size.x / 2.0 + shape2Size.x / 2.0);
            double intersectY = abs(offsetY) - (shape1Size.y / 2.0 + shape2Size.y / 2.0);

            // Verificar si la intersección en el eje X es mayor que la intersección en el eje Y
            if (intersectX > intersectY) {
                // Verificar la dirección de la colisión en el eje X y ajustar la posición de la hitbox del pie
                if (offsetX > 0) {
                    player.FeetHitbox.setPosition(shape2Position.x + boundingBox2.width + shape1Size.x / 2, shape1Position.y);
                } else {
                    player.FeetHitbox.setPosition(shape2Position.x - boundingBox1.width - shape1Size.x / 2, shape1Position.y);
                }
            } else {
                // Verificar la dirección de la colisión en el eje Y y ajustar la posición de la hitbox del pie
                if (offsetY > 0) {
                    player.FeetHitbox.setPosition(shape1Position.x, shape2Position.y + boundingBox2.height + shape1Size.y); // <- Esta es la única
                                                                                                // Colisión funcional (al pasar por debajo del muro)
                                                                                                // Mañana hago el resto
                } else {
                    player.FeetHitbox.setPosition(shape1Position.x, shape2Position.y - boundingBox1.height - shape1Size.y / 2);
                }
            }

            // Ajustar la posición del sprite del jugador para corregir la colisión
            sf::Vector2f playerPosition = player.playerCurrentSprite.getPosition();
            sf::Vector2f playerFeetPosition = sf::Vector2f(playerPosition.x, shape1Position.y + shape1Size.y);
            sf::Vector2f playerFeetOffset = playerFeetPosition - playerPosition;
            player.playerCurrentSprite.setPosition(player.FeetHitbox.getPosition() - playerFeetOffset);
        }

        player.update(deltaTime);

        window.clear();
        window.draw(wall);
        window.draw(player);
        window.display();
    }
}