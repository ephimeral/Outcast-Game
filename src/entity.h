#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"

class Entity : public sf::Drawable
{
protected:
    sf::Sprite currentSprite;
public:
    AnimationSprite animation;
public:

            // Constructor - Destructor //

    Entity();
    ~Entity();


            // Funciones virtuales, aca se movera la implementación general de Player cuando empecemos a hacer los enemigos //
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void update(float deltaTime);
    virtual sf::RectangleShape* getFeetHitbox();
    virtual sf::RectangleShape* getBodyHitbox();
    virtual sf::RectangleShape* getPunchHitbox();
    virtual sf::Vector2f getCurrentPosition();
    virtual void setCurrentPosition(sf::Vector2f position);
};