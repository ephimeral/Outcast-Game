#include <SFML/Graphics.hpp>
#include "stage.h"
#include "player.h"
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
void Stage::loadTextureMap()
{
}

void Stage::loadPlayer(std::shared_ptr<Player>& player)
{
    this->player = player;
    addEntities(player);
}

void Stage::loadEnemies()
{
}

void Stage::loadWorldObjects(std::shared_ptr<WorldObject> worldObject)
{
    this->worldObjects.push_back(worldObject);
    addEntities(worldObject);
}

void Stage::addEntities(std::shared_ptr<Entity>& entity)
{
    this->entities.push_back(entity);
}

void Stage::addEntities(std::shared_ptr<WorldObject>& worldObject)
{
    this->entities.push_back(worldObject);
}

void Stage::addEntities(std::shared_ptr<Player>& player)
{
    this->entities.push_back(player);
    this->movableEntities.push_back(player);
}



        // Getters //


std::vector<std::shared_ptr<Entity>> Stage::getEntities() const
{
	return this->entities;
}

std::shared_ptr<Player> Stage::getPlayer() const
{
	return this->player;
}

std::vector<std::shared_ptr<Entity>> Stage::getMovableEntities() const
{
    return this->movableEntities;
}

std::vector<std::shared_ptr<WorldObject>> Stage::getWorldObjects() const
{
    return this->worldObjects;
}
