#include "Public/JumpCard.h"

#include "Public/JumpRound.h"

JumpCard::JumpCard(const EColor& color)
    :Card{"Jump Card", color}
{}

std::string JumpCard::GetCardTypeName() const
{
    return "Jump";
}

EntityPtr<Round> JumpCard::GetCustomRound(const int roundIndex)
{
    return static_cast<EntityPtr<Round>>(EntityPtr<JumpRound>::MakeEntityPtr(roundIndex));
}

bool JumpCard::CanBeTossed(EntityPtr<Card> other)
{
    if(other.IsValid())
    {
        const auto jumpCard = static_cast<EntityPtr<JumpCard>>(other);
        if(jumpCard.IsValid())
        {
            return true;
        }
    }

    return Card::CanBeTossed(other);
}