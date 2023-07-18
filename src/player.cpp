#include <SFML/Graphics.hpp>
#include "player.h"
#include "animation.h"
#include <iostream>

struct Frame{
    int pixelLeftOrigin;
    int topPixel;
    int width;
    int height;
    int pixelesDistanciaFrame;
    int totalFrames;
};

void setFrames(std::vector<sf::IntRect>& vectorFrames, Frame& frame)
{
    for (int i = 0; i < frame.totalFrames; i++, frame.pixelLeftOrigin += frame.pixelesDistanciaFrame)
    {
        vectorFrames[i] = sf::IntRect(frame.pixelLeftOrigin, frame.topPixel, frame.width, frame.height);
    } 
}

Player::Player(std::unique_ptr<sf::Texture>& spriteSheet, sf::Vector2f position) : animation(){


	//Inicialización del player, establecer su textura principal y su posición en la pantalla
    this->texture = std::move(spriteSheet);
    currentSprite.setTexture(*texture);
    currentSprite.setTextureRect(sf::IntRect(15, 10, 22, 38));
    currentSprite.setPosition(position);


    // Calcular bounds del sprite
    sf::FloatRect spriteBounds = currentSprite.getLocalBounds();
    std::cout << spriteBounds.width << " height:" << spriteBounds.height << std::endl;

    //Establecer hitbox del cuerpo
    this->BodyHitbox.setSize(sf::Vector2f(spriteBounds.width / 2.0f, spriteBounds.height / 1.7f));
    BodyHitbox.setFillColor(sf::Color::Transparent);
    BodyHitbox.setOutlineColor(sf::Color::Red);
    BodyHitbox.setOutlineThickness(2.0f);

    // Establecer Hitbox de los pies
    this->FeetHitbox.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height / 5.5f));
    FeetHitbox.setFillColor(sf::Color::Transparent);
    FeetHitbox.setOutlineColor(sf::Color::Green);
    FeetHitbox.setOutlineThickness(2.0f);

    //Establecer Hitbox de los puños
    this->PunchHitbox.setSize(sf::Vector2f(spriteBounds.width / 5.0f, spriteBounds.height / 5.0f));
    PunchHitbox.setFillColor(sf::Color::Transparent);
    PunchHitbox.setOutlineColor(sf::Color::Blue);
    PunchHitbox.setOutlineThickness(2.0f);

    //Definición de los frames de cada animación, son vectores que serán pasados a animation para que los guarde

    Frame frameIdleFrames{15, 10, 22, 38, 49, 5};
    std::vector<sf::IntRect> idleFrames(5);
    setFrames(idleFrames, frameIdleFrames);


    Frame frameRunFrames{13, 56, 41, 38, 42, 4};
    std::vector<sf::IntRect> runFrames(4);
    setFrames(runFrames, frameRunFrames);


    Frame framePunchFrames{11, 116, 37, 35, 49, 15};
    std::vector<sf::IntRect> punchFrames(15);
    setFrames(punchFrames, framePunchFrames);


    animation.setIdleAnimation(idleFrames);
    animation.setRunAnimation(runFrames);
    animation.setPunchAnimation(punchFrames);
    animation.setEntityCurrentSprite(&currentSprite);
}; 

Player::~Player () { std::cout << "Player destroyed" << std::endl;} 


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw dibujara la variable "currentSprite" que es la que es alterada en la animación
    target.draw(currentSprite, states);

    // Dibujar hitboxes para visualizarlas
    target.draw(BodyHitbox, states);
    target.draw(FeetHitbox, states);
    if (animation.isPunching)
        target.draw(PunchHitbox, states);
}

void Player::update(float deltaTime)
{


    sf::Vector2f movement(0.0f, 0.0f);
    static bool faceLeft = true; // Este bool establece si estamos viendo a la izquierda o la derecha


    if (animation.isPunching) // Esto es para bloquear el input de movimiento al golpear
    {						  // Sientete libre de cambiarlo cuando vayas a hacer el sistema de combate (vas a tener que cambiarlo esto se ve horrible)
        animation.punchUpdate(deltaTime, faceLeft);
    }
    else //Yandere simulator:
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            animation.isPunching = true;
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
                animation.idleUpdate(deltaTime, faceLeft);
            }
            else
            {
                animation.runUpdate(deltaTime, faceLeft);
            }
        }
    }

    //Actualizacion de las hitboxes y el movimiento

    currentSprite.move(movement);

    sf::Vector2f position = currentSprite.getPosition();
    sf::FloatRect spriteBounds = currentSprite.getLocalBounds();

    BodyHitbox.setPosition(position.x + spriteBounds.width / 4.0f, position.y + spriteBounds.height / 5.0f);
    FeetHitbox.setPosition(position.x, position.y + spriteBounds.height / 1.3f);

    if (animation.isPunching){
        if (faceLeft)
            PunchHitbox.setPosition(position.x - spriteBounds.width / 5.0f, position.y + spriteBounds.height / 2.0f);
        else
            PunchHitbox.setPosition(position.x + spriteBounds.width / 3.0f, position.y + spriteBounds.height / 2.0f);
    }
}