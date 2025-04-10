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
    this->chestSprite->setScale({1.6f, 1.6f});
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

void Chest::render(sf::RenderTarget &target)
{
    if (chestSprite)
    {
        target.draw(*this->chestSprite);
    }
}

void Chest::update()
{
    bool animationFinished = false;
    if (this->chestAnimationTimer.getElapsedTime().asSeconds() >= this->animationSpeed && animationFinished == false)
    {
        this->frameIndex++;
        if (this->frameIndex == 5)
        {
            animationFinished = true;
            this->frameIndex = 0;
        }
        if (this->questionType == 1)
        {
            this->currentFrame = sf::IntRect({this->frameIndex * 40, 0 * 38}, {40, 38});
        }
        else if (this->questionType == 2)
        {
            this->currentFrame = sf::IntRect({this->frameIndex * 40, 0 * 36}, {40, 36});
        }
        else if (this->questionType == 2)
        {
            this->currentFrame = sf::IntRect({this->frameIndex * 40, 0 * 32}, {40, 32});
        }
        this->chestAnimationTimer.restart();
    }
}

int Chest::getPointsGained(int pointsGained) const
{
    return this->pointsGained;
}

int Chest::getQuestionType(int questionType) const
{
    return this->questionType;
}
float Chest::getSpawnChance() const
{
    return this->spawnChance;
}

void Chest::setPosition(sf::Vector2f newPos)
{
    this->chestSprite->setPosition(newPos);
}

sf::Sprite &Chest::getSprite()
{
    return *this->chestSprite;
}