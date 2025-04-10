#ifndef CHEST_H
#define CHEST_H

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Exceptions.h"

class Chest
{
protected:
    sf::Texture chestTexture;
    std::unique_ptr<sf::Sprite> chestSprite;
    int pointsGained;
    int questionType;
    float spawnChance;

    sf::Clock chestAnimationTimer;
    sf::IntRect currentFrame;
    float animationSpeed = 0.1f;
    int frameIndex = 0;

public:
    Chest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType);
    virtual std::string genQuestion() = 0;

    virtual std::unique_ptr<Chest> clone() const = 0;
    // Returns a smart pointer which cointains a Chest object(or derived)
    // Clone a polymorphic object(copy an object w/o knowing exactly his real type)

    Chest(const Chest &other);
    Chest &operator=(const Chest &other);

    int getPointsGained(int pointsGained) const;
    float getSpawnChance() const;
    int getQuestionType(int questionType) const;
    void update();
    void render(sf::RenderTarget &target);
    void setPosition(sf::Vector2f newPos);

    sf::Sprite &getSprite();

    virtual ~Chest() = default;
};

#endif