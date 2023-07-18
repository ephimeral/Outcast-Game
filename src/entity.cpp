#include "entity.h"
#include <SFML/Graphics.hpp>


Entity::Entity()
{
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(currentSprite, states);
}

void Entity::update(float deltaTime)
{
}