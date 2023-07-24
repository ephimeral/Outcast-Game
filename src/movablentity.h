#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"

class MovableEntity : public sf::Drawable
{
protected:
    float speed = 400.0f;
    std::unique_ptr<sf::Texture> texture;
    AnimationSprite animation;

                // Hitbox variables //
    sf::RectangleShape           FeetHitbox;
    sf::RectangleShape           BodyHitbox;
    sf::RectangleShape           PunchHitbox;
public:
    bool isMoving = false;
    bool isPunching = false;
    sf::Sprite currentSprite;
public:

            // Constructor - Destructor //

    MovableEntity(MovableEntity&& other) noexcept;
    MovableEntity();
    MovableEntity& operator=(MovableEntity&& other) noexcept;
    ~MovableEntity();


            // Funciones virtuales, aca se movera la implementación general de Player cuando empecemos a hacer los enemigos //
    virtual void                    draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void                    update(float deltaTime);
    virtual sf::RectangleShape&     getFeetHitbox();
    virtual sf::RectangleShape&     getBodyHitbox();
    virtual sf::RectangleShape&     getPunchHitbox();
    virtual sf::Vector2f            getCurrentPosition();
    virtual sf::Sprite&             getCurrentSprite();
    virtual void                    setCurrentPosition(sf::Vector2f position);
};