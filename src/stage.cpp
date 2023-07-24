#include <SFML/Graphics.hpp>
#include "stage.h"
#include <utility>
#include <iostream>



        // Constructores - Destructores //

Stage::Stage()
{
}


Stage::Stage(sf::Texture& mapTexture)
{
	this->mapTexture = mapTexture;
}

Stage::~Stage()
{
}


        // Load functions //

    
void Stage::addPlayer(std::unique_ptr<Player>&& player)
{
    this->player = std::move(player);
}

void Stage::addMovableEntity(MovableEntity&& entity)
{
    this->movableEntities.push_back(std::move(entity));
}

void Stage::addEvent(std::unique_ptr<Event>& event)
{
    this->events.push_back(std::move(event));
}

void Stage::addStaticEntity(StaticEntity&& staticEntity)
{
    this->staticEntities.push_back(std::move(staticEntity));   
}


                    // Getters //

std::vector<StaticEntity>&  Stage::getStaticEntities()
{
    return this->staticEntities;
}

std::vector<MovableEntity>& Stage::getMovableEntities()
{
    return this->movableEntities;
}

std::vector<std::unique_ptr<Event>>& Stage::getEvents()
{
    return this->events;
}

std::unique_ptr<Player>& Stage::getPlayer()
{
    return this->player;
}