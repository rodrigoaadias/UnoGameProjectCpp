#include "Public/MustBuyCard.h"

MustBuyCard::MustBuyCard(const EColor& color, int amountToBuy)
    : Card{"Buy +" + std::to_string(amountToBuy), color}, AmountToBuy{amountToBuy}
{}

int MustBuyCard::GetAmountToBuy() const
{
    return AmountToBuy;
}