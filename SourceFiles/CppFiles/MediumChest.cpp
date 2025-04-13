#include "../HeaderFiles/MediumChest.h"

MediumChest::MediumChest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType)
    : Chest(pathToTexture, pointsGained, spawnChance, questionType)
{
    this->currentFrame = sf::IntRect({0, 0 * 36}, {48, 36});
    this->chestSprite->setTextureRect(this->currentFrame);
}

std::string MediumChest::genQuestion()
{
    return "90-45-90";
}
std::string MediumChest::solveQuestion(std::string question)
{
    int total = 0;
    int currNumber = 0;
    int i = 0;
    std::vector<int> numbers;
    std::vector<char> operators;
    while (i < question.size())
    {
        if (isdigit(question[i]))
        {
            currNumber = 0;
            while (i < question.size() && isdigit(question[i]))
            {
                currNumber = currNumber * 10 + (question[i] - '0');
                i++;
            }
            numbers.push_back(currNumber);
            if (i < question.size() - 1)
            {
                operators.push_back(question[i]);
                i++;
            }
        }
        else
        {
            if (question[i] == '+' || question[i] == '-')
            {
                operators.push_back(question[i]);
            }
            i++;
        }
    }
    if (numbers.size() == operators.size())
    {
        if (operators[0] == '+')
            total = numbers[0];
        else
            total = -numbers[0];
        for (int j = 1; j < numbers.size(); j++)
        {
            if (operators[j] == '+')
                total = total + numbers[j];
            else if (operators[j] == '-')
                total = total - numbers[j];
        }
    }
    else
    {
        total = numbers[0];
        for (int j = 1; j < numbers.size(); j++)
        {
            if (operators[j - 1] == '+')
                total = total + numbers[j];
            else if (operators[j - 1] == '-')
                total = total - numbers[j];
        }
    }
    return std::to_string(total);
}

std::unique_ptr<Chest> MediumChest::clone() const
{
    auto cloned = std::make_unique<MediumChest>(*this);
    cloned->chestSprite = std::make_unique<sf::Sprite>(*this->chestSprite);
    return cloned;
}