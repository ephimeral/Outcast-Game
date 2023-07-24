#include "game.h"
#include "stagebuilder.h"
#include <SFML/Window.hpp>
#include <utility>
#include <memory>
#include <iostream>
#include <typeinfo>

        // Constructor - Destructor //
Game::Game()
: gameWindow(sf::VideoMode(1280, 720), "Outcast Game is going Bitches"),
stageBuilder(this)
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
    currentStage->getPlayer()->update(deltaTime); // Actualizar player

    for (auto& entity : currentStage->getMovableEntities()) // Actualizar entidades movibles
    {
        entity.update(deltaTime);
    }
}

void Game::gameRender() // Renderiza todas las entidades del stage
{
    gameWindow.clear();

    gameWindow.draw(*currentStage->getPlayer()); // Dibujar al player

    for (auto& movableEntity : currentStage->getMovableEntities())
    {
        gameWindow.draw(movableEntity);
    }

    for (auto& staticEntity : currentStage->getStaticEntities())
    {
        gameWindow.draw(staticEntity);
    }

    for (auto& event : currentStage->getEvents())
    {
        gameWindow.draw(*event);
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

    auto& player = *currentStage->getPlayer();

    for (auto& staticEntity : currentStage->getStaticEntities())
    {
        if (player.isPunching)
        {
            checkHurtboxCollision(player);
            continue;
        }

        if (checkCollision(player.getFeetHitbox(), staticEntity.getStaticHitbox()))
        {
            resolveCollision(player.getFeetHitbox(), staticEntity.getStaticHitbox(), player);
        }

        for (auto& event : currentStage->getEvents())
        {
            if (checkCollision(player.getFeetHitbox(), event->getEventHitbox()))
            {
                event->run();
            }
        }
    }

    // for (auto& movableEntity : currentStage->getMovableEntities())
    // {
        
    //     if (movableEntity.isPunching)
    //     {
    //         checkHurtboxCollision(movableEntity);
    //         continue;
    //     }


    //     for (auto& staticEntity : currentStage->getStaticEntities())
    //     {
    //         if (checkCollision(movableEntity.getFeetHitbox(), staticEntity.getStaticHitbox()))
    //         {
    //             resolveCollision(movableEntity.getFeetHitbox(), staticEntity.getStaticHitbox(), movableEntity);
    //         }
    //     }
    // }
}

void Game::checkHurtboxCollision(MovableEntity& movableEntity) // Esta función es para comprobar las colisiones entre
{                                                // las hitbox de los golpes y todas las BodyHitbox del stage
    for (auto& entityHurtbox : currentStage->getMovableEntities())
    {
        if(checkCollision(movableEntity.getPunchHitbox(), entityHurtbox.getBodyHitbox()))
        {
            // Resolve collision
        }
    }
}

bool Game::checkCollision(const sf::RectangleShape& box1, const sf::RectangleShape& box2) {
    return box1.getGlobalBounds().intersects(box2.getGlobalBounds());
}

void Game::resolveCollision(sf::RectangleShape& box1, const sf::RectangleShape& box2, MovableEntity& entity) // Resuelve la colisión entre
{                                                                                                     // Una entidad movible y un objeto estático
    sf::FloatRect boundingBox1 = box1.getGlobalBounds();
    sf::FloatRect boundingBox2 = box2.getGlobalBounds();

    sf::Vector2f entityPosition = entity.getCurrentPosition();

    sf::Vector2f entityFeetPosition = sf::Vector2f(entityPosition.x, boundingBox1.top + boundingBox1.height);
    sf::Vector2f entityFeetOffset = entityFeetPosition - entityPosition;

    float intersectionDepthX = std::min(boundingBox1.left + boundingBox1.width - boundingBox2.left, boundingBox2.left + boundingBox2.width - boundingBox1.left);
    float intersectionDepthY = std::min(boundingBox1.top + boundingBox1.height - boundingBox2.top, boundingBox2.top + boundingBox2.height - boundingBox1.top);

    if (intersectionDepthX < intersectionDepthY) {
        if (boundingBox1.left + boundingBox1.width / 2.0f < boundingBox2.left + boundingBox2.width / 2.0f) {
            box1.move(-intersectionDepthX, 0.0f);
            entity.setCurrentPosition(entityPosition - sf::Vector2f(intersectionDepthX, 0.0f));
        } else {
            box1.move(intersectionDepthX, 0.0f);
            entity.setCurrentPosition(entityPosition + sf::Vector2f(intersectionDepthX, 0.0f));
        }
    } else {
        if (boundingBox1.top + boundingBox1.height / 2.0f < boundingBox2.top + boundingBox2.height / 2.0f) {
            box1.move(0.0f, -intersectionDepthY);
            entity.setCurrentPosition(entityPosition - sf::Vector2f(0.0f, intersectionDepthY));
        } else {
            box1.move(0.0f, intersectionDepthY);
            entity.setCurrentPosition(entityPosition + sf::Vector2f(0.0f, intersectionDepthY));
        }
    }
}