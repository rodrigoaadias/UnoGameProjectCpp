#include "Public/NumberCard.h"

NumberCard::NumberCard(const EColor color, const int number)
    : Card{ "Number Card " + std::to_string(number) , color}, Number{number}
{}

std::string NumberCard::GetCardTypeName() const
{
    return std::to_string(Number);
}

bool NumberCard::CanTossCardOnMe(const EntityPtr<Card>& other) const
{
    if(other.IsValid())
    {
        EntityPtr<NumberCard> otherNumberCard = static_cast<EntityPtr<NumberCard>>(other);
        if(otherNumberCard.IsValid() &&
            otherNumberCard->GetNumber() == Number)
        {
            return true;
        }
    }

    return Card::CanTossCardOnMe(other);
}