#include "worldobject.h"
#include "animation.h"
#include <iostream>

WorldObject::~WorldObject()
{
    std::cout << "World object destroy" << std::endl;
}




WorldObject::WorldObject(std::unique_ptr<sf::Texture>& spriteSheet, sf::Vector2f position)
{

    std::cout << "World Object created" << std::endl;
    //Inicialización del object, establecer su textura principal y su posición en la pantalla
    this->texture = std::move(spriteSheet);
    currentSprite.setTexture(*texture);
    currentSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
    currentSprite.setPosition(position);

    // Calcular bounds y pocision del sprite
    sf::FloatRect spriteBounds = currentSprite.getLocalBounds();
    sf::Vector2f spritePosition = currentSprite.getPosition();
    //Establecer hitbox del object
    this->ObjectHitbox.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
    ObjectHitbox.setFillColor(sf::Color::Transparent);
    ObjectHitbox.setOutlineColor(sf::Color::Red);
    ObjectHitbox.setOutlineThickness(2.0f);
    ObjectHitbox.setPosition(spritePosition);

}


void WorldObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(currentSprite, states);
    target.draw(ObjectHitbox, states);
}



void WorldObject::update(float deltaTime)
{
}


sf::RectangleShape WorldObject::getObjectHitbox()
{
    return this->ObjectHitbox;
}