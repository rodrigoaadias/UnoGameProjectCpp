#include "Public/JumpCard.h"

#include "Core/Public/Engine.h"
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
    return static_cast<EntityPtr<Round>>(Engine::CreateEntity<JumpRound>(roundIndex));
}

bool JumpCard::CanTossCardOnMe(const EntityPtr<Card>& other) const
{
    if(other.IsValid())
    {
        const auto jumpCard = static_cast<EntityPtr<JumpCard>>(other);
        if(jumpCard.IsValid())
        {
            return true;
        }
    }

    return Card::CanTossCardOnMe(other);
}