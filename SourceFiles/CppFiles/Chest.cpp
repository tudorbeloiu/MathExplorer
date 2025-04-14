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
    this->animationFinished = false;
    this->frameIndex = 0;
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

void Chest::update(sf::Clock chestAnimationTimer)
{
    if (chestAnimationTimer.getElapsedTime().asSeconds() >= this->animationSpeed && animationFinished == false)
    {
        this->frameIndex++;
        if (this->frameIndex == 5)
        {
            animationFinished = true;
            this->frameIndex = 4;
        }
        if (this->questionType == 1)
        {
            this->currentFrame = sf::IntRect({this->frameIndex * 48, 0 * 38}, {48, 38});
        }
        else if (this->questionType == 2)
        {
            this->currentFrame = sf::IntRect({this->frameIndex * 48, 0 * 36}, {48, 36});
        }
        else if (this->questionType == 3)
        {
            this->currentFrame = sf::IntRect({this->frameIndex * 48, 0 * 32}, {48, 32});
        }
        this->chestSprite->setTextureRect(this->currentFrame);
        chestAnimationTimer.restart();
    }
}

int Chest::generateRandomNumber(int min, int max)
{
    // create a static random device, used only once to seed the generator
    static std::random_device rd;

    // initialize a "Mersenne Twister" random number generator with the random device seed
    static std::mt19937 gen(rd());

    // create an uniform int distribution between given parameters
    // this ensures that every number in the range has an equal chance
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int Chest::getPointsGained() const
{
    return this->pointsGained;
}

int Chest::getQuestionType() const
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

bool Chest::getAnimationFinished()
{
    return this->animationFinished;
}

sf::Sprite &Chest::getSprite()
{
    return *this->chestSprite;
}