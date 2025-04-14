#include "../HeaderFiles/MediumChest.h"

MediumChest::MediumChest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType)
    : Chest(pathToTexture, pointsGained, spawnChance, questionType)
{
    this->currentFrame = sf::IntRect({0, 0 * 36}, {48, 36});
    this->chestSprite->setTextureRect(this->currentFrame);
}

std::string MediumChest::genQuestion()
{
    std::string question = "";
    int operationGenerator = this->generateRandomNumber(0, 1);
    if (operationGenerator == 0)
    {
        int number1 = this->generateRandomNumber(0, 50);
        int number2 = this->generateRandomNumber(1, 50);

        question = std::to_string(number1) + "*" + std::to_string(number2);
    }
    else if (operationGenerator == 1)
    {
        bool condition = false;
        int number1 = 0;
        int number2 = 0;
        do
        {
            condition = true;
            number1 = this->generateRandomNumber(20, 2500);
            number2 = this->generateRandomNumber(2, number1 - 1);
            if (number1 % number2 != 0)
                condition = false;
        } while (condition == false);
        question = std::to_string(number1) + ":" + std::to_string(number2);
    }
    return question;
}
std::string MediumChest::solveQuestion(std::string question)
{
    int total = 0;
    int currNumber = 0;
    int i = 0;
    int myOp;
    std::vector<int> numbers;
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
                if (question[i] == '*')
                    myOp = 1;
                else
                    myOp = 2;
                i++;
            }
        }
    }
    total = numbers[0];
    if (myOp == 1)
        total = total * numbers[1];
    else
        total = total / numbers[1];

    return std::to_string(total);
}

std::unique_ptr<Chest> MediumChest::clone() const
{
    auto cloned = std::make_unique<MediumChest>(*this);
    cloned->chestSprite = std::make_unique<sf::Sprite>(*this->chestSprite);
    return cloned;
}