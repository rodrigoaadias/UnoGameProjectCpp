#include "Public/ReverseCard.h"

ReverseCard::ReverseCard(const EColor& color)
    : Card{"Reverse card", color}
{}

std::string ReverseCard::GetCardTypeName() const
{
    return "Reverse";
}

bool ReverseCard::CanBeTossed(EntityPtr<Card> other)
{
    if(other.IsValid())
    {
        const auto reverseCard = static_cast<EntityPtr<ReverseCard>>(other);
        if(reverseCard.IsValid())
        {
            return true;
        }
    }

    return Card::CanBeTossed(other);
}

void ReverseCard::Execute(Match* currentMatch)
{
    currentMatch->ReverseFlow();
}