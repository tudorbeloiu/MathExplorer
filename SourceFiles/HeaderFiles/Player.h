#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

enum PlayerStates
{
    IDLE = 0,
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN,
};

class Player
{
private:
    Player() = default; // private constructor, only the builder is using it

    friend class PlayerBuilder;

    sf::Texture playerTextureIdle;
    sf::Texture playerTextureWalk;
    sf::Sprite *player;

    sf::Vector2f velocity;
    float movementSpeed;

    sf::Clock dt_clock;
    float dt;

    sf::IntRect currentFrame;
    sf::Clock animationTimer;

    float animationSpeed = 0.1f;
    short animationState = 0;
    int frameIndex = 0;

    void initTexture();
    void initSprite();

public:
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

    void updateMovement(float dt);
    void updateCollision(sf::RenderTarget *target);
    void updateAnimations();

    void render(sf::RenderTarget *target);

    void setSpawnPoint(sf::Vector2f spawnPoint);
    sf::Sprite &getSprite();
    sf::Vector2f getVelocity();
    void setVelocity(sf::Vector2f velocity);
    void setPosition(sf::Vector2f setPos);
    void updateAnimationsForMainMenu();

    virtual ~Player();
};

#endif