#ifndef PLAYERBUILDER_H
#define PLAYERBUILDER_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Player.h"

class PlayerBuilder
{
private:
    Player *player;

public:
    PlayerBuilder();

    PlayerBuilder &setMovementSpeed(const float movementSpeed);
    PlayerBuilder &setSPoint(sf::Vector2f posPlayer);
    PlayerBuilder &setPlayerScale(sf::Vector2f scalePlayer);
    PlayerBuilder &setPlayerVelocity(sf::Vector2f playerVelocity);

    Player *build();

    virtual ~PlayerBuilder() = default;
};

#endif