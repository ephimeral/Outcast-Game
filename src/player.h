#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "entity.h"
#include <memory>
class Player : public Entity
{
private:
    float speed = 400.0f;
    std::unique_ptr<sf::Texture> texture;

                // Hitbox variables //
    sf::RectangleShape           FeetHitbox;
    sf::RectangleShape           BodyHitbox;
    sf::RectangleShape           PunchHitbox;

public:
    AnimationSprite              animation;

public:
                    // Constructor - Destructor //
    ~Player();
    Player(std::unique_ptr<sf::Texture>& spriteSheet, sf::Vector2f position);


                    // Render functions //
    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void            update(float deltaTime);

                    // Setters //
    void            setCurrentPosition(sf::Vector2f position);


                    // Getters //
    sf::Vector2f            getCurrentPosition();
    sf::RectangleShape*     getFeetHitbox();
    sf::RectangleShape*     getBodyHitbox();
    sf::RectangleShape*     getPunchHitbox();
};
