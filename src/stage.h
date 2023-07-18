#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include "entity.h"
#include <memory>
#include <utility>

class Stage
{
private:
	std::shared_ptr<Player>	  					  player;
	sf::Texture  			  					  mapTexture;
	sf::Sprite 				  					  mapSprite;
	//std::vector<std::shared_ptr<Enemy>> 	      enemies;
	std::vector<std::shared_ptr<Entity>>		  entities;
	//std::vector<std::shared_ptr<WorldObjects>>  worldObjects;
	std::vector<sf::Vector2f> 					  worldStaticHitboxesCoordinates;
	std::vector<sf::Vector2f> 					  hurtboxesCoordinates;
	std::vector<sf::Vector2f> 					  damageBoxesCoordinates;

public:
	bool isStage;

public:

	Stage();
	Stage(sf::Texture& mapTexture);

						// Funciones Loaders //
	// Estas funciones son las encargadas de definir los miembros de "Stage"
	// Son construidas en el StageBuilder

	void loadTextureMap();
	void loadPlayer(std::shared_ptr<Player>& player);
	void loadEnemies();
	void loadWorldObjects();

						// Setters //

	void setEnemiesPosition();
	void setWorldObjectsPosition();
	void addEntities(std::shared_ptr<Entity>& entity);
	void addEntities(std::shared_ptr<Player>& player);
	// void addEntities(std::shared_ptr<Enemy> enemy);
	// void addEntities(std::shared_ptr<WorldObject> worldObject);


						// Getters //

	std::shared_ptr<Player>					getPlayer() const;
	//std::vector<Enemy> 					getEnemies() const;
	std::vector<std::shared_ptr<Entity>>	getEntities() const;
	//std::vector<WorldObjects> 			getWorldObjects() const;
	std::vector<sf::Vector2f> 				getWorldStaticHitboxesCoordinates() const;
	std::vector<sf::Vector2f> 				getHurtboxesCoordinates() const;
	std::vector<sf::Vector2f> 				getDamageBoxesCoordinates() const;



};