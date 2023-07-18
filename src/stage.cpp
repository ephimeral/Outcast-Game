#include <SFML/Graphics.hpp>
#include "stage.h"
#include "player.h"
#include <utility>
#include <iostream>

Stage::Stage()
{
}


Stage::Stage(sf::Texture& mapTexture)
{
	this->mapTexture = mapTexture;
}



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


void Stage::loadWorldObjects()
{
}


void Stage::addEntities(std::shared_ptr<Entity>& entity)
{
    this->entities.push_back(entity);
}


void Stage::addEntities(std::shared_ptr<Player>& player)
{
    this->entities.push_back(player);
}

void Stage::setEnemiesPosition()
{
}


void Stage::setWorldObjectsPosition()
{
}


std::vector<std::shared_ptr<Entity>> Stage::getEntities() const
{
	return this->entities;
}

std::shared_ptr<Player> Stage::getPlayer() const
{
	return this->player;
}


// std::vector<Enemy> Stage::getEnemies()
// {
// 	return this->enemies;
// }


// std::vector<WorldObjects> Stage::getWorldObjects()
// {

// }


// std::vector<sf::Vector2f> Stage::getWorldStaticHitboxesCoordinates()
// {
// }


// std::vector<sf::Vector2f> Stage::getHurtboxesCoordinates()
// {
// }


// std::vector<sf::Vector2f> Stage::getDamageBoxesCoordinates()
// {
// }
