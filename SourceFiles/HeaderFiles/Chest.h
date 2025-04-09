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

public:
    Chest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType);
    virtual std::string genQuestion() = 0;
    virtual int getPointsGained() = 0;

    virtual std::unique_ptr<Chest> clone() const = 0;
    // Returns a smart pointer which cointains a Chest object(or derived)
    // Clone a polymorphic object(copy an object w/o knowing exactly his real type)

    Chest(const Chest &other);
    Chest &operator=(const Chest &other);

    virtual float getSpawnChance() const = 0;
    int getQuestionType() const;

    virtual ~Chest() = default;
};

#endif