#pragma once
#include "Card.h"

class MustBuyCard : Card
{
    int AmountToBuy;
    
public:
    MustBuyCard(const EColor& color, int amountToBuy);

    int GetAmountToBuy() const;
};
