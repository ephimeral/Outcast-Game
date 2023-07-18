#include "game.h"
#include "stagebuilder.h"
#include <utility>
#include <memory>
#include <iostream>
        // if (checkCollision(player.FeetHitbox, wall.body))
        // {
        //     // Variables de tamaño y posición de las hitboxes y sprites
        //     sf::Vector2f shape1Position = player.FeetHitbox.getPosition();
        //     sf::Vector2f shape2Position = wall.body.getPosition();
        //     sf::Vector2f shape1Size = player.FeetHitbox.getSize();
        //     sf::FloatRect boundingBox1 = player.FeetHitbox.getGlobalBounds();
        //     sf::FloatRect boundingBox2 = wall.body.getGlobalBounds();
        //     sf::Vector2f spriteSize = player.SpriteHitbox.getSize();
        //     sf::Vector2f shape2Size = wall.body.getSize();

        //     double offsetX = (boundingBox1.left + boundingBox1.width / 2.0) - (boundingBox2.left + boundingBox2.width / 2.0);
        //     double offsetY = (boundingBox1.top + boundingBox1.height / 2.0) - (boundingBox2.top + boundingBox2.height / 2.0);

        //     double intersectX = abs(offsetX) - (shape1Size.x / 2.0 + shape2Size.x / 2.0);
        //     double intersectY = abs(offsetY) - (shape1Size.y / 2.0 + shape2Size.y / 2.0);

        //     // Verificar si la intersección en el eje X es mayor que la intersección en el eje Y
        //     if (intersectX > intersectY) {
        //         // Verificar la dirección de la colisión en el eje X y ajustar la posición de la hitbox del pie
        //         if (offsetX > 0) {
        //             player.FeetHitbox.setPosition(shape2Position.x + boundingBox2.width + shape1Size.x / 2, shape1Position.y);
        //         } else {
        //             player.FeetHitbox.setPosition(shape2Position.x - boundingBox1.width - shape1Size.x / 2, shape1Position.y);
        //         }
        //     } else {
        //         // Verificar la dirección de la colisión en el eje Y y ajustar la posición de la hitbox del pie
        //         if (offsetY > 0) {
        //             player.FeetHitbox.setPosition(shape1Position.x, shape2Position.y + boundingBox2.height + shape1Size.y); // <- Esta es la única
        //                                                                                         // Colisión funcional (al pasar por debajo del muro)
        //                                                                                         // Mañana hago el resto
        //         } else {
        //             player.FeetHitbox.setPosition(shape1Position.x, shape2Position.y - boundingBox1.height - shape1Size.y / 2);
        //         }
        //     }

        //     // Ajustar la posición del sprite del jugador para corregir la colisión
        //     sf::Vector2f playerPosition = player.playerCurrentSprite.getPosition();
        //     sf::Vector2f playerFeetPosition = sf::Vector2f(playerPosition.x, shape1Position.y + shape1Size.y);
        //     sf::Vector2f playerFeetOffset = playerFeetPosition - playerPosition;
        //     player.playerCurrentSprite.setPosition(player.FeetHitbox.getPosition() - playerFeetOffset);
        // }


Game::Game()
: gameWindow(sf::VideoMode(1280, 720), "Outcast Game is going Bitches"),
stageBuilder()
{
	this->gameWindow.setFramerateLimit(60);

}


void Game::run()
{
	float deltaTime = 0.0f;
    sf::Clock clock;
    sf::Event event;

    // Crear un objeto Stage
    std::unique_ptr<Stage> stage = std::make_unique<Stage>();

    stageBuilder.setDebugRoom(*stage); // Establecer el stage a "debugroom"

    // Mover el pointer stage a currentStage
    currentStage = std::move(stage);
    while (gameWindow.isOpen())
    {

        deltaTime = clock.restart().asSeconds();

        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
        }

        if (currentStage->isStage) //Comprobar si estamos en un stage o un menu antes de ejecutar las colisiones
	        checkCollisions();
        gameUpdate(deltaTime);

        gameRender();
    }
}

void Game::checkCollisions()
{
}

void Game::gameUpdate(float deltaTime)
{
	for (auto& entity : currentStage->getEntities())
	{
		entity->update(deltaTime);
	}
}

void Game::gameRender()
{
	gameWindow.clear();

	for (auto& entity : currentStage->getEntities())
	{
		gameWindow.draw(*entity);
	}

	gameWindow.display();
}