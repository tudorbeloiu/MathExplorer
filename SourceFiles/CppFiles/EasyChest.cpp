#include "../HeaderFiles/EasyChest.h"

std::string EasyChest::genQuestion()
{
    return "90+45";
}

std::unique_ptr<Chest> EasyChest::clone() const
{
    return std::make_unique<EasyChest>(*this);
}