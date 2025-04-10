#include "../HeaderFiles/MediumChest.h"

std::string MediumChest::genQuestion()
{
    return "90*45";
}

std::unique_ptr<Chest> MediumChest::clone() const
{
    return std::make_unique<MediumChest>(*this);
}