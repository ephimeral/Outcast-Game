#pragma once
#include "SFML/Graphics.hpp"

class Game;
class EventFactory;

class Event : public sf::Drawable
{
typedef void (EventFactory::*EventFunction)();
private:
	Game* game;
    EventFactory* eventFactory;
    
    EventFunction eventFunction;
	sf::RectangleShape	eventHitbox;
public:

            // Constructor | Destructor //

	Event(sf::Vector2f position, sf::Vector2f size, Game* game, EventFactory* eventFactory, EventFunction eventFunction);
	~Event();

            // Render //
    void    	        draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void            	update(float deltaTime);

    
    sf::RectangleShape& getEventHitbox();
    void 				run();

};