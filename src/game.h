#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "stage.h"
#include "stagebuilder.h"
#include <memory>

class Game
{
private:
	StageBuilder 	 	   stageBuilder;
	std::unique_ptr<Stage> currentStage;
	sf::RenderWindow 	   gameWindow;

public:
	Game();
	void run();
	void loadStage();
	void unloadStage();
	void checkCollisions();
	void checkWorldCollisions();
	void checkCombatCollisions();
	void gameUpdate(float deltaTime);
	void gameRender();
};