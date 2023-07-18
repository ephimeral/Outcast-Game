#include "stagebuilder.h"
#include "player.h"
#include "stage.h"
#include <iostream>


StageBuilder::StageBuilder()
{
}

void StageBuilder::setDebugRoom(Stage& stage)
{
    sf::Texture spritesheet_pj;
    if (!spritesheet_pj.loadFromFile("src/images/spritesheet.png"))
        std::cout << "Error loading texture" << std::endl;

    // Por algún motivo el jugador es renderizado como un enorme cuadro blanco
    // Sospecho que tiene que ver con la vida util de la textura, pero no estoy seguro
    // Mañana (17 de julio) buscaré una solución, estoy cansado y no doy mas
    
    std::shared_ptr<Player> player = std::make_shared<Player>(spritesheet_pj, sf::Vector2f(640, 320));

    stage.loadPlayer(player);
	stage.isStage = true;
}