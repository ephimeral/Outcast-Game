#pragma once
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "collider.h"
//Clase de Player, en un futuro la mayoría de sus funcionés serán movidas a un base class "Entity" de la que 
//heredarán todas las entidades del juego

class Player : public sf::Drawable 
{
private:
    float speed = 400.0f;
    sf::RectangleShape BodyHitbox;
    sf::RectangleShape PunchHitbox;
public:
    sf::Sprite playerCurrentSprite;
    AnimationSprite animation;
    sf::RectangleShape FeetHitbox;
    sf::RectangleShape SpriteHitbox; // <- estas pendejadas no deberian ser publicas pero para la simplicidad de la prueba estarán así
                                    // hasta que lo re-escriba
public:

    Player(sf::Texture* spriteSheet);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Collider getCollider() {return Collider(FeetHitbox);}

    void update(float deltaTime);
};
