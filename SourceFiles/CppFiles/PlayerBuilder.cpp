#include "../HeaderFiles/PlayerBuilder.h"

PlayerBuilder::PlayerBuilder()
{
    player = new Player();
    player->animationState = IDLE;
    player->initTexture();
    player->initSprite();
}

PlayerBuilder &PlayerBuilder::setMovementSpeed(const float movement_Speed)
{
    player->movementSpeed = movement_Speed;
    return *this;
}

PlayerBuilder &PlayerBuilder::setSPoint(sf::Vector2f posPlayer)
{
    player->setSpawnPoint(posPlayer);
    return *this;
}

PlayerBuilder &PlayerBuilder::setPlayerScale(sf::Vector2f scalePlayer)
{
    player->getSprite().setScale(scalePlayer);
    return *this;
}

PlayerBuilder &PlayerBuilder::setPlayerVelocity(sf::Vector2f playerVelocity)
{
    player->setVelocity(playerVelocity);
    return *this;
}

Player *PlayerBuilder::build()
{
    return player;
}