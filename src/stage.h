#pragma once
#include <SFML/Graphics.hpp>
#include "staticentity.h"
#include "player.h"
#include "event.h"
#include <memory>
#include <utility>



// Posible performance boost al utilizar semanticas de movimiento enves de smart pointers
// En un futuro lo haré, ahora no tengo ganas
class Stage
{
private:
	sf::Texture  			  					  mapTexture;
	sf::Sprite 				  					  mapSprite;
	std::unique_ptr<Player>						  player;
	std::vector<MovableEntity>		  			  movableEntities;
	std::vector<StaticEntity>					  staticEntities;
	std::vector<std::unique_ptr<Event>>			  events;

public:
	bool isStage;

public:
				// Constructor - Destructor //
	Stage();
	Stage(sf::Texture& mapTexture);
	~Stage();


						// Setters //
	
	void addMovableEntity(MovableEntity&& movableEntity);
	void addPlayer(std::unique_ptr<Player>&& player);
	void addEvent(std::unique_ptr<Event>& event);
	void addStaticEntity(StaticEntity&& staticEntity);


						// Getters //

	std::vector<StaticEntity>&				getStaticEntities();
	std::unique_ptr<Player>&				getPlayer();
	std::vector<MovableEntity>&				getMovableEntities();
	std::vector<std::unique_ptr<Event>>&	getEvents();				
};