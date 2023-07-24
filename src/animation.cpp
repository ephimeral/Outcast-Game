#include "animation.h"
#include "movablentity.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>




            // Constructor - Destructor //

AnimationSprite::AnimationSprite(Player* player)
{
    this->player = player;
    std::cout << "[OBJECT] AnimationSprite created" << std::endl;
}
AnimationSprite::AnimationSprite()
{
    std::cout << "[OBJECT] Empty constructor - AnimationSprite created" << std::endl;
}

AnimationSprite::~AnimationSprite()
{
    std::cout << "[OBJECT] AnimationSprite destroyed" << std::endl;
}

AnimationSprite::AnimationSprite(AnimationSprite&& other) noexcept
    : player(std::move(other.player)),
      vectorIdleFrames(std::move(other.vectorIdleFrames)),
      vectorRunFrames(std::move(other.vectorRunFrames)),
      vectorPunchFrames(std::move(other.vectorPunchFrames)),
      FRAME_DURATION(other.FRAME_DURATION)
{
    std::cout << "[MOVE CONSTRUCTOR] AnimationSprite Moved" << std::endl;
}

AnimationSprite& AnimationSprite::operator=(AnimationSprite&& other) noexcept
{
    if (this != &other)
    {
        player = std::move(other.player);
        vectorIdleFrames = std::move(other.vectorIdleFrames);
        vectorRunFrames = std::move(other.vectorRunFrames);
        vectorPunchFrames = std::move(other.vectorPunchFrames);
        FRAME_DURATION = other.FRAME_DURATION;
        std::cout << "[MOVE OPERATOR] AnimationSprite Moved" << std::endl;
    }
    return *this;
}


            // Setters //

void AnimationSprite::setFrames(std::vector<sf::IntRect>& vectorFrames, Frame& frame)
{
    for (int i = 0; i < frame.totalFrames; i++, frame.pixelLeftOrigin += frame.pixelesDistanciaFrame)
    {
        vectorFrames[i] = sf::IntRect(frame.pixelLeftOrigin, frame.topPixel, frame.width, frame.height);
    } 
}

void AnimationSprite::setIdleAnimation(std::vector<sf::IntRect>& vectorIdleFrames)
{
    this->vectorIdleFrames = vectorIdleFrames;
}

void AnimationSprite::setRunAnimation(std::vector<sf::IntRect>& vectorRunFrames)
{
    this->vectorRunFrames = vectorRunFrames;
}

void AnimationSprite::setPunchAnimation(std::vector<sf::IntRect>& vectorPunchFrames)
{
    this->vectorPunchFrames = vectorPunchFrames;
}






//Funciones de update, encargadas de actualizar el "entityCurrentSprite" cada vez que son llamadas


void AnimationSprite::updateAnimation(float deltaTime, bool faceLeft, std::vector<sf::IntRect>& vectorFrames, int& indexImage, int frameOffset)
{
    static float elapsedTime = 0.0f;

    elapsedTime += deltaTime;

    if (elapsedTime >= FRAME_DURATION)
    {
        sf::IntRect currentImage = vectorFrames[indexImage];

        if (!faceLeft)
        {
            currentImage.left += frameOffset;
            currentImage.width = -abs(currentImage.width);
        }
        else
        {
            currentImage.left = currentImage.left;
            currentImage.width = abs(currentImage.width);
        }

        player->currentSprite.setTextureRect(currentImage);
        if (indexImage >= vectorFrames.size() - 1)
            indexImage = 0;
        else
            indexImage++;

        elapsedTime = 0.0f;
    }
}

void AnimationSprite::idleUpdate(float deltaTime, bool faceLeft)
{
    static int indexImage = 0;

    updateAnimation(deltaTime, faceLeft, vectorIdleFrames, indexImage, 21);
}

void AnimationSprite::runUpdate(float deltaTime, bool faceLeft)
{
    static int indexImage = 0;

    updateAnimation(deltaTime, faceLeft, vectorRunFrames, indexImage, 38);
}

void AnimationSprite::punchUpdate(float deltaTime, bool faceLeft)
{

    //BUG: No se muestra correctamente la animación del golpe //
    static int indexPunchImage = 0;

    updateAnimation(deltaTime, faceLeft, vectorPunchFrames, indexPunchImage, 37);

    if (indexPunchImage == 0)
        player->isPunching = false;
}



