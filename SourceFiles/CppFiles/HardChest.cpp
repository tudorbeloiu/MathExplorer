#include "../HeaderFiles/HardChest.h"

HardChest::HardChest(const std::string &pathToTexture, int pointsGained, float spawnChance, int questionType)
    : Chest(pathToTexture, pointsGained, spawnChance, questionType)
{
    this->currentFrame = sf::IntRect({0, 0 * 32}, {48, 32});
    this->chestSprite->setTextureRect(this->currentFrame);
}
std::string HardChest::solveQuestion(std::string question)
{
    int i = 0;
    std::string coefA = "", coefB = "", coefC = "";
    std::string current = "";
    std::string solution = "";
    while (i < question.size() && (question[i] != 'X'))
    {
        current = current + question[i];
        i++;
    }
    i = i + 2;
    coefA = coefA + current;
    if (current == "-")
        coefA = coefA + "1";
    else if (current == "")
        coefA = "1";
    i++;
    if (question[i] != '=')
    {
        current = "";
        while (i < question.size() && (question[i] != 'X' && question[i] != '='))
        {
            current = current + question[i];
            i++;
        }
        if (question[i] == '=')
        {
            coefB = "0";
            coefC = coefC + current;
            if (current[0] == '+')
                coefC = coefC.substr(1);
        }
        else if (question[i] == 'X')
        {
            if (current == "+")
                coefB = coefB + current + "1";
            else if (current == "-")
                coefB = coefB + current + "1";
            else if (current.size() > 1)
                coefB = coefB + current;
            if (current[0] == '+')
                coefB = coefB.substr(1);
            i++;
            current = "";
            while (i < question.size() && question[i] != '=')
            {
                current = current + question[i];
                i++;
            }
            if (current == "")
                coefC = coefC + "0";
            else
                coefC = coefC + current;
            if (current[0] == '+')
                coefC = coefC.substr(1);
        }
    }
    else
    {
        coefB = "0";
        coefC = "0";
    }

    int a = std::atoi(coefA.c_str());
    int b = std::atoi(coefB.c_str());
    int c = std::atoi(coefC.c_str());

    int delta = b * b - (4 * a * c);
    if (delta < 0)
        return "impossible";
    else if (delta == 0)
    {
        if (b % (2 * a) == 0)
        {
            int X1 = -b / (2 * a);
            return std::to_string(X1);
        }
        return "NULL";
    }
    else if (delta > 0)
    {
        double sqrtDelta = std::sqrt(delta);
        if (std::floor(sqrtDelta) == sqrtDelta)
        {
            double X1 = (-b - sqrtDelta) / (2.0 * a);
            double X2 = (-b + sqrtDelta) / (2.0 * a);

            if (std::floor(X1) == X1 && std::floor(X2) == X2)
            {
                if (X1 < X2)
                    return std::to_string(static_cast<int>(X1)) + " " + std::to_string(static_cast<int>(X2));
                else
                    return std::to_string(static_cast<int>(X2)) + " " + std::to_string(static_cast<int>(X1));
            }
            return "NULL";
        }
        return "NULL";
    }
    return "NULL";
}

std::string HardChest::genQuestion()
{
    std::string question = "";
    std::string ok = "";
    do
    {

        question = "";
        int coefPozNeg = this->generateRandomNumber(0, 1);
        int coefA = this->generateRandomNumber(1, 10);
        if (coefA == 1)
        {
            if (coefPozNeg == 0)
                question = question + "X^2";
            else
                question = question + "-" + "X^2";
        }
        else
        {
            if (coefPozNeg == 0)
                question = question + std::to_string(coefA) + "X^2";
            else
                question = question + "-" + std::to_string(coefA) + "X^2";
        }

        coefPozNeg = this->generateRandomNumber(0, 1);
        int coefB = this->generateRandomNumber(0, 10);

        if (coefB == 1)
        {
            if (coefPozNeg == 0)
                question = question + "+X";
            else
                question = question + "-" + "X";
        }
        else if (coefB > 1)
        {
            if (coefPozNeg == 0)
                question = question + "+" + std::to_string(coefB) + "X";
            else
                question = question + "-" + std::to_string(coefB) + "X";
        }

        coefPozNeg = this->generateRandomNumber(0, 1);
        int coefC = this->generateRandomNumber(0, 10);

        if (coefC == 1)
        {
            if (coefPozNeg == 0)
                question = question + "+1=0";
            else
                question = question + "-1=0";
        }
        else if (coefC == 0)
        {
            question = question + "=0";
        }
        else
        {
            if (coefPozNeg == 0)
                question = question + "+" + std::to_string(coefC) + "=0";
            else
                question = question + "-" + std::to_string(coefC) + "=0";
        }

        ok = solveQuestion(question);
    } while (ok == "NULL");

    return question;
}

Chest *HardChest::clone() const
{
    return new HardChest(*this);
}