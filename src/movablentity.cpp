#include "movablentity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

MovableEntity::MovableEntity(){ std::cout << "[OBJECT] Movable entity created" << std::endl;}

MovableEntity::~MovableEntity() { std::cout << "[OBJECT] Movable entity destroyed" << std::endl;}
            // Move constructor //
MovableEntity::MovableEntity(MovableEntity&& other) noexcept
        : speed(other.speed),
          currentSprite(std::move(other.currentSprite)),
          texture(std::move(other.texture)),
          FeetHitbox(std::move(other.FeetHitbox)),
          BodyHitbox(std::move(other.BodyHitbox)),
          animation(std::move(other.animation)),
          PunchHitbox(std::move(other.PunchHitbox)),
          isMoving(other.isMoving),
          isPunching(other.isPunching)
{
    std::cout << "[MOVE CONSTRUCTOR] Movable Entity Moved" << std::endl;
}

MovableEntity& MovableEntity::operator=(MovableEntity&& other) noexcept
{
    if (this != &other)
    {
        speed = other.speed;
        currentSprite = std::move(other.currentSprite);
        texture = std::move(other.texture);
        animation = std::move(other.animation);
        FeetHitbox = std::move(other.FeetHitbox);
        BodyHitbox = std::move(other.BodyHitbox);
        PunchHitbox = std::move(other.PunchHitbox);
        isMoving = other.isMoving;
        isPunching = other.isPunching;
        std::cout << "[MOVE OPERATOR] Movable Entity Moved" << std::endl;
    }
    return *this;
}

void MovableEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Draw dibujara la variable "currentSprite" que es la que es alterada en la animación
    target.draw(currentSprite, states);
    

        // DEBUGGING //
    target.draw(BodyHitbox, states);
    target.draw(FeetHitbox, states);
    if (isPunching)           
        target.draw(PunchHitbox, states);
}


void MovableEntity::update(float deltaTime)
{
}

        // MOVABLE ENTITY CLASSES //

sf::RectangleShape& MovableEntity::getFeetHitbox()
{
    return FeetHitbox;
}

sf::RectangleShape& MovableEntity::getPunchHitbox()
{
    return PunchHitbox;
}

sf::RectangleShape& MovableEntity::getBodyHitbox()
{
    return BodyHitbox;
}

void MovableEntity::setCurrentPosition(sf::Vector2f position)
{
    currentSprite.setPosition(position);
}

sf::Vector2f MovableEntity::getCurrentPosition()
{
    return currentSprite.getPosition();
}

sf::Sprite& MovableEntity::getCurrentSprite()
{
    return currentSprite;
}