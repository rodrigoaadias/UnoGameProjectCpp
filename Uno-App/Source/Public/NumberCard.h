#pragma once
#include "Card.h"

class NumberCard : public Card
{
    int Number;
public:
    NumberCard(EColor color, int number);

    int GetNumber() const { return Number; }
    std::string GetCardTypeName() const override;
};
