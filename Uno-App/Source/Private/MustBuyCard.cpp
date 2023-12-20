#include "Public/MustBuyCard.h"

MustBuyCard::MustBuyCard(const EColor& color, int amountToBuy)
    : Card{"Buy +" + std::to_string(amountToBuy), color}, AmountToBuy{amountToBuy}
{}

int MustBuyCard::GetAmountToBuy() const
{
    return AmountToBuy;
}

std::string MustBuyCard::GetCardTypeName() const
{
    return "+" + std::to_string(AmountToBuy);
}

bool MustBuyCard::CanBeTossed(EntityPtr<Card> other)
{
    if(other.IsValid())
    {
        const auto mustBuyCard = static_cast<EntityPtr<MustBuyCard>>(other);
        if(mustBuyCard.IsValid() &&
            mustBuyCard->GetAmountToBuy() == AmountToBuy)
        {
            return true;
        }
    }

    return Card::CanBeTossed(other);
}