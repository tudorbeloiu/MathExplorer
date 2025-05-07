#ifndef PLAYERBUILDER_H
#define PLAYERBUILDER_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Player.h"

enum PlayerStates
{
    IDLE = 0,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN,
};

template <typename T>
class PlayerBuilder
{
private:
    T *player;

public:
    PlayerBuilder()
    {
        player = new T();
        player->animationState = IDLE;
        player->initTexture();
        player->initSprite();
    }

    PlayerBuilder &setMovementSpeed(const float movementSpeed)
    {
        player->movementSpeed = movementSpeed;
        return *this;
    }

    PlayerBuilder &setSPoint(sf::Vector2f posPlayer)
    {
        player->setSpawnPoint(posPlayer);
        return *this;
    }

    PlayerBuilder &setPlayerScale(sf::Vector2f scalePlayer)
    {
        player->getSprite().setScale(scalePlayer);
        return *this;
    }

    PlayerBuilder &setPlayerVelocity(sf::Vector2f playerVelocity)
    {
        player->setVelocity(playerVelocity);
        return *this;
    }

    T *build()
    {
        return player;
    }

    virtual ~PlayerBuilder() = default;
};

#endif