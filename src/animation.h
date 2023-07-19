#pragma once
#include <SFML/Graphics.hpp>



// Esta clase contendrá las animaciones de las entidades del juego 
// Debe instanciarse dentro de cada entidad, pues cada una dispone de su propia animación

class AnimationSprite
{
private:
    sf::Sprite* entityCurrentSprite;

    std::vector<sf::IntRect> vectorIdleFrames;
    std::vector<sf::IntRect> vectorRunFrames;
    std::vector<sf::IntRect> vectorPunchFrames;

    const float FRAME_DURATION = 0.1f; // Establece la duración entre cada cambio de frame

public:
    bool isPunching = false;

public:


            // Constructor - Destructor //
    AnimationSprite();
    ~AnimationSprite();


            // Setters de frames //
    void setIdleAnimation(std::vector<sf::IntRect> vectorIdleFrames);
    void setRunAnimation(std::vector<sf::IntRect> vectorRunFrames);
    void setPunchAnimation(std::vector<sf::IntRect> vectorPunchFrames);
    void setEntityCurrentSprite(sf::Sprite* entityCurrentSprite);


            // Funciones update, actualizará la entidad //
    void idleUpdate(float deltaTime, bool faceLeft);
    void runUpdate(float deltaTime, bool faceLeft);
    void punchUpdate(float deltaTime, bool faceLeft);

};