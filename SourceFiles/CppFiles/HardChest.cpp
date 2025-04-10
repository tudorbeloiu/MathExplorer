#include "../HeaderFiles/HardChest.h"

std::string HardChest::genQuestion()
{
    return "sqrt(90*45)";
}

std::unique_ptr<Chest> HardChest::clone() const
{
    return std::make_unique<HardChest>(*this);
}