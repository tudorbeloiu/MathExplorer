#include "../HeaderFiles/EasyChest.h"

EasyChest::EasyChest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType)
    : Chest(pathToTexture, pointsGained, spawnChance, questionType)
{
    this->currentFrame = sf::IntRect({0, 0 * 38}, {48, 38});
    this->chestSprite->setTextureRect(this->currentFrame);
}

std::string EasyChest::genQuestion()
{
    return "90+45";
}

std::unique_ptr<Chest> EasyChest::clone() const
{
    auto cloned = std::make_unique<EasyChest>(*this);
    cloned->chestSprite = std::make_unique<sf::Sprite>(*this->chestSprite);
    return cloned;
}