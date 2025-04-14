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
    int countNumbers = this->generateRandomNumber(2, 7);
    int countOperators = countNumbers - 1;
    int countParanthesis = this->generateRandomNumber(0, std::round(countNumbers / 2.f) - 1);

    std::vector<bool> openPar(countNumbers, false);
    std::vector<bool> closePar(countNumbers, false);

    std::set<std::pair<int, int>> parPairs;
    while (parPairs.size() < countParanthesis)
    {
        int start = this->generateRandomNumber(0, countNumbers - 2);
        int end = this->generateRandomNumber(start + 1, countNumbers - 1);

        bool overlay = false;
        for (const auto &p : parPairs)
        {
            if (!(end < p.first || start > p.second))
            {
                overlay = true;
                break;
            }
        }
        if (overlay == false)
        {
            parPairs.insert(std::make_pair(start, end));
            openPar[start] = true;
            closePar[end] = true;
        }
    }
    for (int i = 0; i < countNumbers; i++)
    {
        if (openPar[i])
        {
            question = question + "(";
        }
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
        if (closePar[i])
        {
            question = question + ")";
        }
    }
    return question;
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