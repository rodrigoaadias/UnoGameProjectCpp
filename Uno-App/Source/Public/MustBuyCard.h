#pragma once
#include "Card.h"

class MustBuyCard : public Card
{
    int AmountToBuy;

public:
    MustBuyCard(const EColor& color, int amountToBuy);

    int GetAmountToBuy() const;

    std::string GetCardTypeName() const override;
    
    bool CanBeTossed(EntityPtr<Card> other) override;
};
