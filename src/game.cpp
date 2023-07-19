#include "game.h"
#include "stagebuilder.h"
#include <utility>
#include <memory>
#include <iostream>




        // Constructor - Destructor //
Game::Game()
: gameWindow(sf::VideoMode(1280, 720), "Outcast Game is going Bitches"),
stageBuilder()
{
    this->gameWindow.setFramerateLimit(60);

}

Game::~Game() {}

        // Funciones de flujo //

void Game::run() // Primera función en ser llamada, inicia el juego //
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

void Game::gameUpdate(float deltaTime) // Actualiza todas las entidades del stage
{
    for (auto& entity : currentStage->getEntities())
    {
        entity->update(deltaTime);
    }
}

void Game::gameRender() // Renderiza todas las entidades del stage
{
    gameWindow.clear();

    for (auto& entity : currentStage->getEntities())
    {
        gameWindow.draw(*entity);
    }

    gameWindow.display();
}



        // Funciones de inicialización de Stage //

void Game::loadStage()
{
}

void Game::unloadStage()
{
}


        // Funciones de Colisión //


void Game::checkCollisions() // Revisa todas las colisiones del stage al iterar en las entidades del stage
{
    for (auto& entity : currentStage->getMovableEntities())
    {
        if (entity->animation.isPunching)
        {
            checkHurtboxCollision(*entity);
        }

        for (auto& worldObject : currentStage->getWorldObjects())
        {
            if (checkCollision(*(entity->getFeetHitbox()),worldObject->getObjectHitbox()))
            {
                resolveCollision(*(entity->getFeetHitbox()), worldObject->getObjectHitbox(), *entity);
            }
        }
    }
}

void Game::checkHurtboxCollision(Entity& entity) // Esta función es para comprobar las colisiones entre
{                                                // las hitbox de los golpes y todas las BodyHitbox del stage
    for (auto& entityHurtbox : currentStage->getMovableEntities())
    {
        if(checkCollision(*(entity.getPunchHitbox()), *(entityHurtbox->getBodyHitbox())))
        {
            // Resolve collision
        }
    }
}

bool Game::checkCollision(const sf::RectangleShape& box1, const sf::RectangleShape& box2) {
    return box1.getGlobalBounds().intersects(box2.getGlobalBounds());
}

void Game::resolveCollision(sf::RectangleShape& box1, const sf::RectangleShape& box2, Entity& player) // Resuelve la colisión entre
{                                                                                                     // Una entidad movible y un objeto estático
    sf::FloatRect boundingBox1 = box1.getGlobalBounds();
    sf::FloatRect boundingBox2 = box2.getGlobalBounds();

    sf::Vector2f playerPosition = player.getCurrentPosition();

    sf::Vector2f playerFeetPosition = sf::Vector2f(playerPosition.x, boundingBox1.top + boundingBox1.height);
    sf::Vector2f playerFeetOffset = playerFeetPosition - playerPosition;

    float intersectionDepthX = std::min(boundingBox1.left + boundingBox1.width - boundingBox2.left, boundingBox2.left + boundingBox2.width - boundingBox1.left);
    float intersectionDepthY = std::min(boundingBox1.top + boundingBox1.height - boundingBox2.top, boundingBox2.top + boundingBox2.height - boundingBox1.top);

    if (intersectionDepthX < intersectionDepthY) {
        if (boundingBox1.left + boundingBox1.width / 2.0f < boundingBox2.left + boundingBox2.width / 2.0f) {
            box1.move(-intersectionDepthX, 0.0f);
            player.setCurrentPosition(playerPosition - sf::Vector2f(intersectionDepthX, 0.0f));
        } else {
            box1.move(intersectionDepthX, 0.0f);
            player.setCurrentPosition(playerPosition + sf::Vector2f(intersectionDepthX, 0.0f));
        }
    } else {
        if (boundingBox1.top + boundingBox1.height / 2.0f < boundingBox2.top + boundingBox2.height / 2.0f) {
            box1.move(0.0f, -intersectionDepthY);
            player.setCurrentPosition(playerPosition - sf::Vector2f(0.0f, intersectionDepthY));
        } else {
            box1.move(0.0f, intersectionDepthY);
            player.setCurrentPosition(playerPosition + sf::Vector2f(0.0f, intersectionDepthY));
        }
    }
}