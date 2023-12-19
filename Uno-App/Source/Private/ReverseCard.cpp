#include "Public/ReverseCard.h"

ReverseCard::ReverseCard(const EColor& color)
    : Card{"Reverse card", color}
{}

std::string ReverseCard::GetCardTypeName() const
{
    return "Reverse";
}