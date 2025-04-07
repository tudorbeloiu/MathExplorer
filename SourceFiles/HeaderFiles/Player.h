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
    sf::Texture playerTextureIdle;
    sf::Texture playerTextureWalk;
    sf::Sprite *player;

    sf::IntRect currentFrame;
    sf::Clock animationTimer;

    float playerSpeed = 3.8f;
    float animationSpeed = 0.1f;
    short animationState = 0;
    int frameIndex = 0;

    void initTexture();
    void initSprite();

public:
    Player();

    void update(const sf::Sprite &back_decor, const sf::Sprite &front_decor, sf::RenderTarget *target);
    void updateMovement();
    void updateCollision(const sf::Sprite &back_decor, const sf::Sprite &front_decor, sf::RenderTarget *target);
    void updateAnimations();

    void render(sf::RenderTarget *target);

    void setSpawnPoint(sf::Vector2f spawnPoint);

    virtual ~Player();
};

#endif