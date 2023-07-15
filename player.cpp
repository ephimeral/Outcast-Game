#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"
#include "animation.cpp"


// Preparate para ver el código más nefasto, spaghetti y asqueroso que vas a visualizar en toda tu vida




Player::Player(sf::Texture* spriteSheet) : animation(spriteSheet){


	//Inicialización del player, establecer su textura principal y su posición en la pantalla

    playerCurrentSprite.setTexture(*spriteSheet);
    playerCurrentSprite.setTextureRect(sf::IntRect(103, 73, 168, 276));
    playerCurrentSprite.setPosition(400, 360);


    // Establecer Hitbox del sprite
    sf::FloatRect spriteBounds = playerCurrentSprite.getLocalBounds();
    this->SpriteHitbox.setSize(sf::Vector2f(spriteBounds.width, spriteBounds.height));
    SpriteHitbox.setFillColor(sf::Color::Transparent);
    SpriteHitbox.setOutlineColor(sf::Color::Red);
    SpriteHitbox.setOutlineThickness(2.0f);    

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

    #define TOP_IDLE 73
    #define HEIGHT_IDLE 168
    #define WIDTH_IDLE 276


    std::vector<sf::IntRect> idleFrames = {
        sf::IntRect(103, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE),
        sf::IntRect(451, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE),
        sf::IntRect(788, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE),
        sf::IntRect(1126, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE),
        sf::IntRect(1456, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE),
        sf::IntRect(1799, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE),
        sf::IntRect(2137, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE),
        sf::IntRect(2464, TOP_IDLE, HEIGHT_IDLE, WIDTH_IDLE)
    };

    #define TOP_RUN 396
    #define HEIGHT_RUN 257
    #define WIDTH_RUN 278


    std::vector<sf::IntRect> runFrames = {
        sf::IntRect(92, TOP_RUN, HEIGHT_RUN, WIDTH_RUN),
        sf::IntRect(379, TOP_RUN, HEIGHT_RUN, WIDTH_RUN),
        sf::IntRect(759, TOP_RUN, HEIGHT_RUN, WIDTH_RUN),
        sf::IntRect(1048, TOP_RUN, HEIGHT_RUN, WIDTH_RUN),
    };


    #define TOP_PUNCH 743
    #define HEIGHT_PUNCH 247
    #define WIDTH_PUNCH 244


    std::vector<sf::IntRect> punchFrames = {
        sf::IntRect(107, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(347, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(677, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(1025, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(1403, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(3780, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(2106, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(2358, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(2690, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(3036, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(3409, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
        sf::IntRect(3797, TOP_PUNCH, HEIGHT_PUNCH, WIDTH_PUNCH),
    };

    animation.setIdleAnimation(idleFrames);
    animation.setRunAnimation(runFrames);
    animation.setPunchAnimation(punchFrames);
    animation.setEntityCurrentSprite(&playerCurrentSprite);
}; 


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw dibujara la variable "playerCurrentSprite" que es la que es alterada en la animación
    target.draw(playerCurrentSprite, states);

    // Dibujar hitboxes para visualizarlas
    target.draw(BodyHitbox, states);
    target.draw(FeetHitbox, states);
    target.draw(SpriteHitbox, states);
    if (animation.isPunching)
        target.draw(PunchHitbox, states);
}

void Player::update(float deltaTime)
{

	// Prepara una bolsa de vomitar porque lo que estás a punto de ver te provocará nauseas



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

    playerCurrentSprite.move(movement);
    sf::Vector2f position = playerCurrentSprite.getPosition();
    sf::FloatRect spriteBounds = playerCurrentSprite.getLocalBounds();
    BodyHitbox.setPosition(position.x + 50, position.y + 50);
    FeetHitbox.setPosition(position.x, position.y + spriteBounds.height - FeetHitbox.getGlobalBounds().height);
    SpriteHitbox.setPosition(position);

    if (animation.isPunching){
        if (faceLeft)
            PunchHitbox.setPosition(position.x - 10, position.y + 130);
        else
            PunchHitbox.setPosition(position.x + 200, position.y + 130);
    }
}