#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"

//Clase de Player, en un futuro la mayoría de sus funcionés serán movidas a un base class "Entity" de la que 
//heredarán todas las entidades del juego

class Player : public sf::Drawable 
{
private:
    sf::Sprite playerCurrentSprite;
    float speed = 400.0f;
public:
    AnimationSprite animation;

public:

    Player(sf::Texture* spriteSheet);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(float deltaTime);
};
