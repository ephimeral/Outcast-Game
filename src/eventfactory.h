#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class Event;
class Game;
class EventFactory
{

private:
	Game* game;

public:

	EventFactory(Game* game);
	EventFactory();
	std::unique_ptr<Event> getDebugEvent(sf::Vector2f position, sf::Vector2f size);


	void functionDebugEvent();
};