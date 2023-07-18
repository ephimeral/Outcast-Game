#include "stagebuilder.h"
#include "player.h"
#include "stage.h"
#include <iostream>


StageBuilder::StageBuilder()
{
}

void StageBuilder::setDebugRoom(Stage& stage)
{
    std::unique_ptr<sf::Texture> spritesheet_pj = std::make_unique<sf::Texture>();
    if (!spritesheet_pj->loadFromFile("src/images/spritesheet.png"))
        std::cout << "Error loading texture" << std::endl;

    std::cout << "Debugroom texture loaded" << std::endl;
    std::shared_ptr<Player> player = std::make_shared<Player>(spritesheet_pj, sf::Vector2f(640, 320));
    std::cout << "Debugroom player created" << std::endl;
    stage.loadPlayer(player);
    std::cout << "Debugroom player loaded" << std::endl;
	stage.isStage = true;
}