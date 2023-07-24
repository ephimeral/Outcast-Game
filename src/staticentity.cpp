#include "staticentity.h"
#include <iostream>

StaticEntity::~StaticEntity()
{
    std::cout << "[OBJECT] StaticEntity destroyed" << std::endl;
}




StaticEntity::StaticEntity(std::unique_ptr<sf::Texture>& spriteSheet, sf::Vector2f position, sf::IntRect& size)
{

    //Inicialización del objeto estático

    texture = std::move(spriteSheet);
    currentSprite.setTexture(*texture);
    currentSprite.setTextureRect(size);
    currentSprite.setPosition(position);

    sf::FloatRect spriteBounds = currentSprite.getLocalBounds();
    sf::Vector2f spritePosition = currentSprite.getPosition();

   StaticHitbox.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
   StaticHitbox.setFillColor(sf::Color::Transparent);
   StaticHitbox.setOutlineColor(sf::Color::Red);
   StaticHitbox.setOutlineThickness(2.0f);
   StaticHitbox.setPosition(spritePosition);
   std::cout << "[OBJECT] StaticEntity created" << std::endl;

}

            // Move constructor //
StaticEntity::StaticEntity(StaticEntity&& other) noexcept
        : texture(std::move(other.texture)),
          StaticHitbox(std::move(other.StaticHitbox)),
          currentSprite(std::move(other.currentSprite))
{
}

void StaticEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(currentSprite, states);
    target.draw(StaticHitbox, states);
}



void StaticEntity::update(float deltaTime)
{
}


sf::RectangleShape& StaticEntity::getStaticHitbox()
{
    return this->StaticHitbox;
}


        // Move operator //
StaticEntity& StaticEntity::operator=(StaticEntity&& other) noexcept
{
    if (this != &other)
        {
            texture = std::move(other.texture);
            StaticHitbox = std::move(other.StaticHitbox);
            currentSprite = std::move(other.currentSprite);
        }
        return *this;
}