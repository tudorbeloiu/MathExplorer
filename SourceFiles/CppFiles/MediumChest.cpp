#include "../HeaderFiles/MediumChest.h"

MediumChest::MediumChest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType)
    : Chest(pathToTexture, pointsGained, spawnChance, questionType)
{
    this->currentFrame = sf::IntRect({0, 0 * 36}, {48, 36});
    this->chestSprite->setTextureRect(this->currentFrame);
}

std::string MediumChest::genQuestion()
{
    return "90*45";
}

std::unique_ptr<Chest> MediumChest::clone() const
{
    auto cloned = std::make_unique<MediumChest>(*this);
    cloned->chestSprite = std::make_unique<sf::Sprite>(*this->chestSprite);
    return cloned;
}