#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "event.h"
#include "game.h"
#include "eventfactory.h"
#include <iostream>

typedef void (EventFactory::*EventFunction)();

Event::Event(sf::Vector2f position, sf::Vector2f size, Game* game, EventFactory* eventFactory, EventFunction eventFunction)
: eventFunction(eventFunction), game(game), eventFactory(eventFactory)
{
	this->eventHitbox.setPosition(position);
    this->eventHitbox.setSize(size);
    this->eventHitbox.setFillColor(sf::Color::Transparent);
    this->eventHitbox.setOutlineColor(sf::Color::Red);
    this->eventHitbox.setOutlineThickness(2.0f);
    std::cout << "[OBJECT] Event created" << std::endl;
}

Event::~Event()
{
	std::cout << "[OBJECT] Event destroyed" << std::endl;
}


void Event::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(eventHitbox, states);
}

void Event::update(float deltaTime)
{
}

void Event::run()
{
	(eventFactory->*eventFunction)();
}

sf::RectangleShape& Event::getEventHitbox()
{
	return this->eventHitbox;
}

