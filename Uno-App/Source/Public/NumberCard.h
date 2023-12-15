#pragma once

#include "Card.h"
#include "EColor.h"

class NumberCard : public Card
{
    int Number;
public:
    NumberCard(EColor color, int number);

    int GetNumber() const { return Number; }
};
