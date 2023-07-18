#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "entity.h"

class Player : public Entity
{
private:
    float speed = 400.0f;
    AnimationSprite              animation;
    std::unique_ptr<sf::Texture> texture;
    sf::RectangleShape           FeetHitbox;
    sf::RectangleShape           BodyHitbox;
    sf::RectangleShape           PunchHitbox;

public:
    sf::Sprite currentSprite;

public:
    ~Player();
    Player(std::unique_ptr<sf::Texture>& spriteSheet, sf::Vector2f position);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(float deltaTime);
};
