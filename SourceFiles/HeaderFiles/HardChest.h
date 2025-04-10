#ifndef HARDCHEST_H
#define HARDCHEST_H

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Chest.h"

class HardChest : public Chest
{
public:
    HardChest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType)
        : Chest(pathToTexture, pointsGained, spawnChance, questionType) {}

    std::string genQuestion() override;

    std::unique_ptr<Chest> clone() const override;
};

#endif