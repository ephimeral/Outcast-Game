#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include "entity.h"
#include "worldobject.h"
#include <memory>
#include <utility>

class Stage
{
private:
	std::shared_ptr<Player>	  					  player;
	sf::Texture  			  					  mapTexture;
	sf::Sprite 				  					  mapSprite;
	//std::vector<std::shared_ptr<Enemy>> 	      enemies;
	std::vector<std::shared_ptr<Entity>>		  movableEntities;
	std::vector<std::shared_ptr<Entity>>		  entities;
	std::vector<std::shared_ptr<WorldObject>>     worldObjects;

public:
	bool isStage;

public:
				// Constructor - Destructor //
	Stage();
	Stage(sf::Texture& mapTexture);
	~Stage();

						// Funciones Loaders //
	// Estas funciones son las encargadas de definir los miembros de "Stage"
	// Son construidas en el StageBuilder

	void loadTextureMap();
	void loadPlayer(std::shared_ptr<Player>& player);
	void loadEnemies();
	void loadWorldObjects(std::shared_ptr<WorldObject> worldObject);

						// Setters //
	
	void addEntities(std::shared_ptr<Entity>& entity);
	void addEntities(std::shared_ptr<Player>& player);
	void addEntities(std::shared_ptr<WorldObject>& worldObject);
	// void addEntities(std::shared_ptr<Enemy> enemy);


						// Getters //

	std::shared_ptr<Player>							getPlayer() const;
	//std::vector<Enemy> 							getEnemies() const;
	std::vector<std::shared_ptr<Entity>>			getEntities() const;
	std::vector<std::shared_ptr<Entity>>			getMovableEntities() const;
	std::vector<std::shared_ptr<WorldObject>> 		getWorldObjects() const;


};