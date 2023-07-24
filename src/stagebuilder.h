#pragma once
#include "stage.h"
#include "eventfactory.h"

class StageBuilder
{
public:
	Game* game;
	EventFactory eventFactory;
public:
	StageBuilder(Game* game);
	void setDebugRoom(Stage& stage);
	void createPlayer(Stage& stage, sf::Vector2f position);
	void createEvent(Stage& stage, sf::Vector2f position, sf::Vector2f size);
	void createWall(Stage& stage, sf::Vector2f position, sf::IntRect size);
	void setSecondDebugRoom(Stage& stage);
};