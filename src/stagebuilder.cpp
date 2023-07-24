#include "stagebuilder.h"
#include "player.h"
#include "staticentity.h"
#include "event.h"
#include <iostream>

StageBuilder::StageBuilder(Game* game) : game(game)
{
    eventFactory = EventFactory(game);
}


void StageBuilder::createPlayer(Stage& stage, sf::Vector2f position)
{
    std::unique_ptr<sf::Texture> spriteSheet_pj = std::make_unique<sf::Texture>();
    if (!spriteSheet_pj->loadFromFile("src/images/spritesheet.png"))
        std::cout << "Error loading texture" << std::endl;

    Frame frameIdleFrames{15, 10, 22, 38, 49, 5}; 
    Frame frameRunFrames{13, 56, 41, 38, 42, 4}; 
    Frame framePunchFrames{11, 116, 37, 35, 49, 15};
    
    std::unique_ptr<Player> player = std::make_unique<Player>(spriteSheet_pj, position, frameIdleFrames, frameRunFrames, framePunchFrames);
    stage.addPlayer(std::move(player));
}

void StageBuilder::createEvent(Stage& stage, sf::Vector2f position, sf::Vector2f size)
{
    std::unique_ptr<Event> event = eventFactory.getDebugEvent(position, size);
    stage.addEvent(event);
}

void StageBuilder::createWall(Stage& stage, sf::Vector2f position, sf::IntRect size)
{
    std::unique_ptr<sf::Texture> spritesheet_wall = std::make_unique<sf::Texture>();
    if (!spritesheet_wall->loadFromFile("src/images/wall.jpg"))
        std::cout << "Error loading texture" << std::endl;
    
    StaticEntity wall(spritesheet_wall, position, size);
    stage.addStaticEntity(std::move(wall));
}

void StageBuilder::setDebugRoom(Stage& stage)
{
	createPlayer(stage, sf::Vector2f(200, 320));
    createWall(stage, sf::Vector2f(500,500), sf::IntRect(0, 0, 200, 200));
    createEvent(stage, sf::Vector2f(100, 100), sf::Vector2f(50, 50));

	stage.isStage = true;
}

void StageBuilder::setSecondDebugRoom(Stage& stage)
{

    createPlayer(stage, sf::Vector2f(640,380));

    createWall(stage, sf::Vector2f(100, 200), sf::IntRect(0, 0, 200, 200));

	stage.isStage = true;
}