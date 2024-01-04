#include "Public/ReverseCard.h"

ReverseCard::ReverseCard(const EColor color)
    : Card{"Reverse card", color}
{}

std::string ReverseCard::GetCardTypeName() const
{
    return "Reverse";
}

bool ReverseCard::CanTossCardOnMe(const EntityPtr<Card>& other) const
{
    if(other.IsValid())
    {
        const auto reverseCard = static_cast<EntityPtr<ReverseCard>>(other);
        if(reverseCard.IsValid())
        {
            return true;
        }
    }

    return Card::CanTossCardOnMe(other);
}

void ReverseCard::Execute(Match* currentMatch)
{
    currentMatch->ReverseFlow();
}