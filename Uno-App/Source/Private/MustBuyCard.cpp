#include "Public/MustBuyCard.h"

#include "Core/Public/Engine.h"
#include "Public/MustBuyRound.h"

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

bool MustBuyCard::CanTossCardOnMe(EntityPtr<Card> other)
{
    if(other.IsValid())
    {
        const auto mustBuyCard = static_cast<EntityPtr<MustBuyCard>>(other);
        if(mustBuyCard.IsValid()
            && mustBuyCard->GetAmountToBuy() == AmountToBuy)
        {
            return true;
        }
    }

    return !IsInRound && Card::CanTossCardOnMe(other);
}

EntityPtr<Round> MustBuyCard::GetCustomRound(int roundIndex)
{
    IsInRound = true;
    return static_cast<EntityPtr<Round>>(Engine::CreateEntity<MustBuyRound>(roundIndex, AmountToBuy + Cumulated));
}

void MustBuyCard::ClearRound()
{
    IsInRound = false;
}

void MustBuyCard::Cumulate(int amount)
{
    Cumulated = amount;
}