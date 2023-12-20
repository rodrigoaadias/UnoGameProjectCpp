#include "Public/JumpCard.h"

JumpCard::JumpCard(const EColor& color)
    :Card{"Jump Card", color}
{}

std::string JumpCard::GetCardTypeName() const
{
    return "Jump";
}

EntityPtr<Round> JumpCard::GetCustomRound(const int roundIndex)
{
    return EntityPtr<Round>::MakeEntityPtr(roundIndex);
}