#include <SFML/Graphics.hpp>
#include "player.h"
#include "animation.h"
#include <iostream>


Player::Player(sf::Texture spriteSheet, sf::Vector2f position) : animation(spriteSheet){


	//Inicialización del player, establecer su textura principal y su posición en la pantalla

    currentSprite.setTexture(spriteSheet);
    currentSprite.setTextureRect(sf::IntRect(15, 10, 38, 22));
    currentSprite.setPosition(position);


    // Calcular bounds del sprite
    sf::FloatRect spriteBounds = currentSprite.getLocalBounds();   

    //Establecer hitbox del cuerpo
    this->BodyHitbox.setSize(sf::Vector2f(spriteBounds.width / 2.0f, spriteBounds.height / 1.7f));
    BodyHitbox.setFillColor(sf::Color::Transparent);
    BodyHitbox.setOutlineColor(sf::Color::Red);
    BodyHitbox.setOutlineThickness(2.0f);

    // Establecer Hitbox de los pies
    this->FeetHitbox.setSize(sf::Vector2f(spriteBounds.width, 45));
    FeetHitbox.setFillColor(sf::Color::Transparent);
    FeetHitbox.setOutlineColor(sf::Color::Green);
    FeetHitbox.setOutlineThickness(2.0f);

    //Establecer Hitbox de los puños
    this->PunchHitbox.setSize(sf::Vector2f(45, 45));
    PunchHitbox.setFillColor(sf::Color::Transparent);
    PunchHitbox.setOutlineColor(sf::Color::Blue);
    PunchHitbox.setOutlineThickness(2.0f);

    //Definición de los frames de cada animación, son vectores que serán pasados a animation para que los guarde

    #define TOP_IDLE 10
    #define HEIGHT_IDLE 38
    #define WIDTH_IDLE 22

    const int TOTAL_IDLE_FRAMES = 5;

    std::vector<sf::IntRect> idleFrames(TOTAL_IDLE_FRAMES);

    for (int i = 0, pixelOrigen = 15, pixelesDistanciaFrame = 49; i < TOTAL_IDLE_FRAMES; i++, pixelOrigen += pixelesDistanciaFrame)
    {
        idleFrames[i] = sf::IntRect(pixelOrigen, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE);
    } 

    #define TOP_RUN 56
    #define HEIGHT_RUN 38
    #define WIDTH_RUN 41

    const int TOTAL_RUN_FRAMES = 4;

    std::vector<sf::IntRect> runFrames(TOTAL_RUN_FRAMES);

    for (int i = 0, pixelOrigen = 13, pixelesDistanciaFrame = 42; i < TOTAL_RUN_FRAMES; i++, pixelOrigen += pixelesDistanciaFrame)
    {
        runFrames[i] = sf::IntRect(pixelOrigen, TOP_RUN, HEIGHT_RUN, WIDTH_RUN);
    } 

    #define TOP_PUNCH 116
    #define HEIGHT_PUNCH 35
    #define WIDTH_PUNCH 37

    const int TOTAL_PUNCH_FRAMES = 15;

    std::vector<sf::IntRect> punchFrames(TOTAL_PUNCH_FRAMES);

    for (int i = 0, pixelOrigen = 11, pixelesDistanciaFrame = 49; i < TOTAL_PUNCH_FRAMES; i++, pixelOrigen += pixelesDistanciaFrame)
    {
        punchFrames[i] = sf::IntRect(pixelOrigen, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE);
    } 


    animation.setIdleAnimation(idleFrames);
    animation.setRunAnimation(runFrames);
    animation.setPunchAnimation(punchFrames);
    animation.setEntityCurrentSprite(&currentSprite);
    std::cout << "Player created" << std::endl;
}; 

Player::~Player () { std::cout << "Player destroyed" << std::endl;} 


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw dibujara la variable "currentSprite" que es la que es alterada en la animación
    target.draw(currentSprite, states);

    // Dibujar hitboxes para visualizarlas
    // target.draw(BodyHitbox, states);
    // target.draw(FeetHitbox, states);
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

    BodyHitbox.setPosition(position.x + 50, position.y + 50);
    FeetHitbox.setPosition(position.x, position.y + spriteBounds.height - FeetHitbox.getGlobalBounds().height);

    if (animation.isPunching){
        if (faceLeft)
            PunchHitbox.setPosition(position.x - 10, position.y + 130);
        else
            PunchHitbox.setPosition(position.x + 200, position.y + 130);
    }
}