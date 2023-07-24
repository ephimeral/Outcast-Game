#include <SFML/Graphics.hpp>
#include "player.h"
#include "animation.h"
#include <iostream>


Player::Player(std::unique_ptr<sf::Texture>& spriteSheet, sf::Vector2f& position, Frame& idleFrames, Frame& runFrames, Frame& punchFrames) : 
animation(this)
{
    texture = std::move(spriteSheet);
    currentSprite.setTexture(*texture);
    currentSprite.setTextureRect(sf::IntRect(idleFrames.pixelLeftOrigin, idleFrames.topPixel, idleFrames.width, idleFrames.height));
    currentSprite.setPosition(position);


                // HITBOXES, GENERALES //
    sf::FloatRect spriteBounds = currentSprite.getLocalBounds();

    BodyHitbox.setSize(sf::Vector2f(spriteBounds.width / 2.0f, spriteBounds.height / 1.7f));
    BodyHitbox.setFillColor(sf::Color::Transparent);
    BodyHitbox.setOutlineColor(sf::Color::Red);
    BodyHitbox.setOutlineThickness(2.0f);

    FeetHitbox.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height / 5.5f));
    FeetHitbox.setFillColor(sf::Color::Transparent);
    FeetHitbox.setOutlineColor(sf::Color::Green);
    FeetHitbox.setOutlineThickness(2.0f);

    PunchHitbox.setSize(sf::Vector2f(spriteBounds.width / 5.0f, spriteBounds.height / 5.0f));
    PunchHitbox.setFillColor(sf::Color::Transparent);
    PunchHitbox.setOutlineColor(sf::Color::Blue);
    PunchHitbox.setOutlineThickness(2.0f);


                 // Frames //

    std::vector<sf::IntRect> vecIdleFrames(idleFrames.totalFrames); 
    animation.setFrames(vecIdleFrames, idleFrames);

    std::vector<sf::IntRect> vecRunFrames(runFrames.totalFrames);
    animation.setFrames(vecRunFrames, runFrames);

    std::vector<sf::IntRect> vecPunchFrames(punchFrames.totalFrames);
    animation.setFrames(vecPunchFrames, punchFrames);


    animation.setIdleAnimation(vecIdleFrames);
    animation.setRunAnimation(vecRunFrames);
    animation.setPunchAnimation(vecPunchFrames);

    std::cout << "[OBJECT] Player created" << std::endl;
}

Player::~Player() { std::cout << "[OBJECT] Player destroyed" << std::endl;}
Player::Player(){}
Player::Player(Player&& other) noexcept
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
    std::cout << "[MOVE CONSTRUCTOR] Player moved" << std::endl;
}

Player& Player::operator=(Player&& other) noexcept
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
        std::cout << "[MOVE OPERATOR] Player Moved" << std::endl;
    }
    return *this;
}

                // UPDATE FUNCTION VIRTUAL //

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Draw dibujara la variable "currentSprite" que es la que es alterada en la animación
    target.draw(currentSprite, states);
        // DEBUGGING //
    target.draw(BodyHitbox, states);
    target.draw(FeetHitbox, states);
    if (isPunching)           
        target.draw(PunchHitbox, states);
}

void Player::update(float deltaTime)
{

    sf::Vector2f movement(0.0f, 0.0f);
    static bool faceLeft = true; // Este bool establece si estamos viendo a la izquierda o la derecha


    if (isPunching)
    {						  
        animation.punchUpdate(deltaTime, faceLeft);
    }
    else //Yandere simulator:
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            isPunching = true;
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                movement.x += speed * deltaTime;
                faceLeft = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                movement.x -= speed * deltaTime;
                faceLeft = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                movement.y -= speed * deltaTime;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                movement.y += speed * deltaTime;
            }

            if (movement.x == 0.0f && movement.y == 0.0f)
            {
                isMoving = false;
                animation.idleUpdate(deltaTime, faceLeft);
            }
            else
            {
                isMoving = true;
                animation.runUpdate(deltaTime, faceLeft);
            }
        }
    }


    currentSprite.move(movement);

    sf::Vector2f position = currentSprite.getPosition();
    sf::FloatRect spriteBounds = currentSprite.getLocalBounds();


    BodyHitbox.setPosition(position.x + spriteBounds.width / 4.0f, position.y + spriteBounds.height / 5.0f);
    FeetHitbox.setPosition(position.x, position.y + spriteBounds.height / 1.3f);

    if (isPunching){
        if (faceLeft)
            PunchHitbox.setPosition(position.x - spriteBounds.width / 5.0f, position.y + spriteBounds.height / 2.0f);
        else
            PunchHitbox.setPosition(position.x + spriteBounds.width / 3.0f, position.y + spriteBounds.height / 2.0f);
    }
}

sf::RectangleShape& Player::getFeetHitbox()
{
    return FeetHitbox;
}

sf::RectangleShape& Player::getPunchHitbox()
{
    return PunchHitbox;
}

sf::RectangleShape& Player::getBodyHitbox()
{
    return BodyHitbox;
}

void Player::setCurrentPosition(sf::Vector2f position)
{
    currentSprite.setPosition(position);
}

sf::Vector2f Player::getCurrentPosition()
{
    return currentSprite.getPosition();
}

sf::Sprite& Player::getCurrentSprite()
{
    return currentSprite;
}