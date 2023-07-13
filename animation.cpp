#include "animation.h"
#include <SFML/Graphics.hpp>

AnimationSprite::AnimationSprite(sf::Texture* spriteSheet)
{
    this->spriteSheet = *spriteSheet;
}


// Estas funciones de inicialización guardaran los frames en la clase
// En un futuro esto será re-escrito para que sea una sola función

void AnimationSprite::setIdleAnimation(std::vector<sf::IntRect> vectorIdleFrames)
{
    this->vectorIdleFrames = vectorIdleFrames;
}

void AnimationSprite::setRunAnimation(std::vector<sf::IntRect> vectorRunFrames)
{
    this->vectorRunFrames = vectorRunFrames;
}

void AnimationSprite::setPunchAnimation(std::vector<sf::IntRect> vectorPunchFrames)
{
    this->vectorPunchFrames = vectorPunchFrames;
}

void AnimationSprite::setEntityCurrentSprite(sf::Sprite* entityCurrentSprite) // Aca le pasamos un pointer, porque lo que queremos es alterar
{																			  // el sprite que le pasaron
    this->entityCurrentSprite = entityCurrentSprite;
}





//Funciones de update, encargadas de actualizar el "entityCurrentSprite" cada vez que son llamadas

void AnimationSprite::idleUpdate(float deltaTime, bool faceLeft)
{
    static float elapsedTime = 0.0f;
    static int indexImage = 0;

    elapsedTime += deltaTime;

    if (elapsedTime >= FRAME_DURATION)
    {
        sf::IntRect currentImage = vectorIdleFrames[indexImage]; //Establece cual es el frame que debemos dibujar

        if (!faceLeft){
            currentImage.left = currentImage.left + 167; // Este numerito mágico es la cantidad de pixeles que se deberá mover 
            currentImage.width = -abs(currentImage.width);// el left del IntRect para que luego sea volteada la imagen usando el valor absoluto negativo
        }
        else{
            currentImage.left = currentImage.left;
            currentImage.width = abs(currentImage.width);   
        }
        entityCurrentSprite->setTextureRect(currentImage); // Establecer el frame al sprite

        if (indexImage >= vectorIdleFrames.size() - 1) // Si ya hemos alcanzado el frame final, reiniciar al frame inicial
            indexImage = 0;
        indexImage++;


        // No comentaré el resto de las funciones Update porque son basicamente lo mismo

        elapsedTime = 0.0f;
    }
}

void AnimationSprite::runUpdate(float deltaTime, bool faceLeft)
{
    static float elapsedTime = 0.0f;
    static int indexImage = 0;

    elapsedTime += deltaTime;

    if (elapsedTime >= FRAME_DURATION)
    {
        sf::IntRect currentImage = vectorRunFrames[indexImage];

        if (!faceLeft){
            currentImage.left = currentImage.left + 269;
            currentImage.width = -abs(currentImage.width);
        }
        else{
            currentImage.left = currentImage.left;
            currentImage.width = abs(currentImage.width);   
        }
        entityCurrentSprite->setTextureRect(currentImage);

        if (indexImage >= vectorRunFrames.size() - 1)
            indexImage = 0;

         elapsedTime = 0.0f;
        indexImage++;
    }
}

void AnimationSprite::punchUpdate(float deltaTime, bool faceLeft)
{
    static float elapsedTime = 0.0f;
    static int indexImage = 0;

    elapsedTime += deltaTime;


    if (elapsedTime >= FRAME_DURATION)
    {
      sf::IntRect currentImage = vectorPunchFrames[indexImage];

      if (!faceLeft){
        currentImage.left = currentImage.left + 248;
        currentImage.width = -abs(currentImage.width);
        }

      else{
        currentImage.left = currentImage.left;
        currentImage.width = abs(currentImage.width);   
        }

      entityCurrentSprite->setTextureRect(currentImage);

      if (indexImage >= vectorPunchFrames.size() - 1){
        indexImage = 0;
        isPunching = false; //Establecer "isPunching" como false para que el usuario pueda moverse
        }


        elapsedTime = 0.0f;
        indexImage++;
    }
}