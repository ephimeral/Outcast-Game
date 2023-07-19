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
			// Constructor - Destructor //
	Game();
	~Game();


			// Funciones de flujo //
	void run();
	void gameUpdate(float deltaTime);
	void gameRender();

			// Funciones de inicialización (Placeholders, aun sin implementación) //
	void loadStage();
	void unloadStage();

			// Funciones de colision //
	void checkCollisions();
	void checkHurtboxCollision(Entity& entity);
	void resolveCollision(sf::RectangleShape& box1, const sf::RectangleShape& box2, Entity& player);
	bool checkCollision(const sf::RectangleShape& box1, const sf::RectangleShape& box2);
};