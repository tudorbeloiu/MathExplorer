#include "../HeaderFiles/HardChest.h"

HardChest::HardChest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType)
    : Chest(pathToTexture, pointsGained, spawnChance, questionType)
{
    this->currentFrame = sf::IntRect({0, 0 * 32}, {48, 32});
    this->chestSprite->setTextureRect(this->currentFrame);
}

std::string HardChest::genQuestion()
{
    return "sqrt(90*45)";
}

std::unique_ptr<Chest> HardChest::clone() const
{
    auto cloned = std::make_unique<HardChest>(*this);
    cloned->chestSprite = std::make_unique<sf::Sprite>(*this->chestSprite);
    return cloned;
}