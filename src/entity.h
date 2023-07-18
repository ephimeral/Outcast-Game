#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
protected:
    sf::Sprite currentSprite;
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void update(float deltaTime);
public:
	Entity();
};