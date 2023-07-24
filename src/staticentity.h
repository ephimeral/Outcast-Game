#pragma once
#include <SFML/Graphics.hpp>


class StaticEntity : public sf::Drawable
{
private:
    std::unique_ptr<sf::Texture> texture;
    sf::RectangleShape           StaticHitbox;
    sf::Sprite 					 currentSprite;
public:
    ~StaticEntity();
    StaticEntity(std::unique_ptr<sf::Texture>& spriteSheet, sf::Vector2f position, sf::IntRect& size);
    StaticEntity(StaticEntity&& other) noexcept;


    StaticEntity& operator=(StaticEntity&& other) noexcept;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void update(float deltaTime);

    sf::RectangleShape& getStaticHitbox();

};