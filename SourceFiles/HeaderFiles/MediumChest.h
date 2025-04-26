#ifndef MEDIUMCHEST_H
#define MEDIUMCHEST_H

#include <iostream>
#include <cmath>
#include <set>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include "Chest.h"

class MediumChest : public Chest
{
public:
    MediumChest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType);

    std::string genQuestion() override;
    std::string solveQuestion(std::string question) override;

    Chest* clone() const override;
};

#endif