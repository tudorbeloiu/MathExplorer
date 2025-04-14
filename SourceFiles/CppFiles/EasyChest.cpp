#include "../HeaderFiles/EasyChest.h"

EasyChest::EasyChest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType)
    : Chest(pathToTexture, pointsGained, spawnChance, questionType)
{
    this->currentFrame = sf::IntRect({0, 0 * 38}, {48, 38});
    this->chestSprite->setTextureRect(this->currentFrame);
}

std::string EasyChest::genQuestion()
{
    std::string question = "";
    int countNumbers = this->generateRandomNumber(2, 7);
    int countOperators = countNumbers - 1;

    for (int i = 0; i < countNumbers; i++)
    {
        int number = this->generateRandomNumber(1, 99);
        question = question + std::to_string(number);
        if (i < countOperators)
        {
            int indexOperator = this->generateRandomNumber(0, 1);
            if (indexOperator == 0)
                question = question + "+";
            else
                question = question + "-";
        }
    }
    return question;
}

std::string EasyChest::solveQuestion(std::string question)
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

std::unique_ptr<Chest> EasyChest::clone() const
{
    auto cloned = std::make_unique<EasyChest>(*this);
    cloned->chestSprite = std::make_unique<sf::Sprite>(*this->chestSprite);
    return cloned;
}