#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "animation.h"


class WorldObject : public Entity
{
private:
    AnimationSprite              animation;
    std::unique_ptr<sf::Texture> texture;
    sf::RectangleShape           ObjectHitbox;
    sf::Sprite 					 currentSprite;
public:
    ~WorldObject();
    WorldObject(std::unique_ptr<sf::Texture>& spriteSheet, sf::Vector2f position);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(float deltaTime);

    sf::RectangleShape getObjectHitbox();

};