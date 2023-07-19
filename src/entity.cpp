#include "entity.h"
#include <SFML/Graphics.hpp>


Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(currentSprite, states);
}

void Entity::update(float deltaTime)
{
}

sf::RectangleShape* Entity::getFeetHitbox()
{
}

sf::RectangleShape* Entity::getBodyHitbox()
{
}

sf::RectangleShape* Entity::getPunchHitbox()
{
}

sf::Vector2f Entity::getCurrentPosition()
{
}

void Entity::setCurrentPosition(sf::Vector2f position)
{
}

