#pragma once
#include <SFML/Graphics.hpp>

// Cabezera de AnimationSprite
// Esta clase será la encargada de tener las animaciones de todas las entidades del juego
// Probablemente en un futuro sea una baseclass y de ella hereden diferentes animaciones para diferentes entidades
// Consta de funciones de inicialización (set) y de actualizacion (update)

class AnimationSprite
{
private:
    sf::Sprite* entityCurrentSprite;
    std::vector<sf::IntRect> vectorIdleFrames;
    std::vector<sf::IntRect> vectorRunFrames;
    std::vector<sf::IntRect> vectorPunchFrames;
    const float FRAME_DURATION = 0.1f;

public: 
    bool isPunching = false;
public:

    AnimationSprite();

    void setIdleAnimation(std::vector<sf::IntRect> vectorIdleFrames);

    void setRunAnimation(std::vector<sf::IntRect> vectorRunFrames);

    void setPunchAnimation(std::vector<sf::IntRect> vectorPunchFrames);

    void setEntityCurrentSprite(sf::Sprite* entityCurrentSprite);

    void idleUpdate(float deltaTime, bool faceLeft);

    void runUpdate(float deltaTime, bool faceLeft);

    void punchUpdate(float deltaTime, bool faceLeft);

};