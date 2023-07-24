#pragma once
#include <SFML/Graphics.hpp>


// Esta clase contendrá las animaciones de las entidades del juego 
// Debe instanciarse dentro de cada entidad, pues cada una dispone de su propia animación
class MovableEntity;
class Player;
struct Frame{
    int pixelLeftOrigin;
    int topPixel;
    int width;
    int height;
    int pixelesDistanciaFrame;
    int totalFrames;
};
class AnimationSprite
{
private:
    Player* player;
    std::vector<sf::IntRect> vectorIdleFrames;
    std::vector<sf::IntRect> vectorRunFrames;
    std::vector<sf::IntRect> vectorPunchFrames;

    float FRAME_DURATION = 0.1f; // Establece la duración entre cada cambio de frame

public:


            // Constructor - Destructor //
    AnimationSprite(Player* player);
    AnimationSprite();
    ~AnimationSprite();
    AnimationSprite(AnimationSprite&& other) noexcept;
    AnimationSprite& operator=(AnimationSprite&& other) noexcept;


            // Setters de frames //
    void setIdleAnimation(std::vector<sf::IntRect>& vectorIdleFrames);
    void setRunAnimation(std::vector<sf::IntRect>& vectorRunFrames);
    void setPunchAnimation(std::vector<sf::IntRect>& vectorPunchFrames);
    void setFrames(std::vector<sf::IntRect>& vectorFrames, Frame& frame);


            // Funciones update, actualizará la entidad //
    void idleUpdate(float deltaTime, bool faceLeft);
    void runUpdate(float deltaTime, bool faceLeft);
    void punchUpdate(float deltaTime, bool faceLeft);
    void updateAnimation(float deltaTime, bool faceLeft, std::vector<sf::IntRect>& vectorFrames, int& indexImage, int frameOffset);


};