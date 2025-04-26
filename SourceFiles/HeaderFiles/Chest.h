#ifndef CHEST_H
#define CHEST_H

#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <string>
#include <cstring>

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

    sf::IntRect currentFrame;
    static constexpr float animationSpeed = 1.5f;
    int frameIndex;
    bool animationFinished;

public:
    Chest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType);
    virtual std::string genQuestion() = 0;
    virtual std::string solveQuestion(std::string question) = 0;

    virtual Chest *clone() const = 0;

    Chest(const Chest &other);
    Chest &operator=(const Chest &other);

    int getPointsGained() const;
    float getSpawnChance() const;
    int getQuestionType() const;
    void update(sf::Clock chestAnimationTimer);
    void render(sf::RenderTarget &target);
    void setPosition(sf::Vector2f newPos);
    int generateRandomNumber(int min, int max);

    bool getAnimationFinished();

    sf::Sprite &getSprite();

    virtual ~Chest() = default;
};

#endif