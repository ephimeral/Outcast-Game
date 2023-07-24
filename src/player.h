#pragma once
#include <SFML/Graphics.hpp>
#include "movablentity.h"
#include "animation.h"
#include <memory>


class Player : public MovableEntity
{
private:
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
    Player(std::unique_ptr<sf::Texture>& spriteSheet, sf::Vector2f& position, Frame& idleFrames, Frame& runFrames, Frame& punchFrames);
    Player();
    ~Player();

    Player(Player&& other) noexcept;
    Player& operator=(Player&& other) noexcept;

    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    sf::RectangleShape& getFeetHitbox() override;
    sf::RectangleShape& getPunchHitbox() override;
    sf::RectangleShape& getBodyHitbox() override;
    void                setCurrentPosition(sf::Vector2f position) override;
    sf::Vector2f        getCurrentPosition() override;
    sf::Sprite&         getCurrentSprite() override;
};
