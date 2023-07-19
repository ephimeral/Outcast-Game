#include "stagebuilder.h"
#include "player.h"
#include "stage.h"
#include "worldobject.h"
#include <iostream>


StageBuilder::StageBuilder()
{
}


		// Placeholder de debugroom //
// La forma en que se construye un stage es definiendo cuales seran sus entidades y luego pasandoselas a "Stage"
// Usamos shared_ptr para no perder la referencia al objeto
// En un futuro cuando estemos armando los stages habrán mas funciones de carga y descarga

void StageBuilder::setDebugRoom(Stage& stage)
{

    std::unique_ptr<sf::Texture> spritesheet_pj = std::make_unique<sf::Texture>();
    if (!spritesheet_pj->loadFromFile("src/images/spritesheet.png"))
        std::cout << "Error loading texture" << std::endl;
    std::shared_ptr<Player> player = std::make_shared<Player>(spritesheet_pj, sf::Vector2f(200, 320));
    stage.loadPlayer(player);


    std::unique_ptr<sf::Texture> spritesheet_wall = std::make_unique<sf::Texture>();
    if (!spritesheet_wall->loadFromFile("src/images/wall.jpg"))
        std::cout << "Error loading texture" << std::endl;
    std::shared_ptr<WorldObject> worldObject = std::make_shared<WorldObject>(spritesheet_wall, sf::Vector2f(200, 200));
    stage.loadWorldObjects(worldObject);

	stage.isStage = true;
}