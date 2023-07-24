#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "stagebuilder.h"

class Stage;

class Game
{
private:
	sf::RenderWindow 	   gameWindow;

public:
	StageBuilder 	 	   stageBuilder;
	std::unique_ptr<Stage> currentStage;
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
	void checkHurtboxCollision(MovableEntity& entity);
	void resolveCollision(sf::RectangleShape& box1, const sf::RectangleShape& box2, MovableEntity& entity);
	bool checkCollision(const sf::RectangleShape& box1, const sf::RectangleShape& box2);
};