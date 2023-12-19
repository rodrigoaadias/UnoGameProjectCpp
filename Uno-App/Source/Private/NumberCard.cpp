#include "Public/NumberCard.h"

NumberCard::NumberCard(const EColor color, const int number)
    : Card{ "Number Card " + std::to_string(number) , color}, Number{number}
{}

std::string NumberCard::GetCardTypeName() const
{
    return std::to_string(Number);
}