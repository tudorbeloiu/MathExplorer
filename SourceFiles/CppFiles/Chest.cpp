#include "../HeaderFiles/Chest.h"

#include <algorithm>

Chest::Chest(const std::string &pathToTexture, int points, float spawnChance, int questionType)
{
    this->pointsGained = points;
    this->spawnChance = spawnChance;
    this->questionType = questionType;
    if (!this->chestTexture.loadFromFile(pathToTexture))
    {
        throw LoadTextureException("Failed to load chest texture from" + pathToTexture);
    }
    this->chestSprite = std::make_unique<sf::Sprite>(this->chestTexture);
}

Chest::Chest(const Chest &other)
{
    this->chestTexture = other.chestTexture;
    this->pointsGained = other.pointsGained;
    this->spawnChance = other.spawnChance;
    this->questionType = other.questionType;
    if (other.chestSprite)
    {
        this->chestSprite = std::make_unique<sf::Sprite>(*other.chestSprite);
    }
}

Chest &Chest::operator=(const Chest &other)
{
    if (this != &other)
    {
        this->chestTexture = other.chestTexture;
        this->pointsGained = other.pointsGained;
        this->spawnChance = other.spawnChance;
        this->questionType = other.questionType;

        if (other.chestSprite)
        {
            this->chestSprite = std::make_unique<sf::Sprite>(*other.chestSprite);
        }
        else
        {
            this->chestSprite.reset();
        }
    }
    return *this;
}

int Chest::getQuestionType() const
{
    return this->questionType;
}
