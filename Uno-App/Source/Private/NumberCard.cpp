#include "Public/NumberCard.h"

NumberCard::NumberCard(const EColor color, const int number)
    : Card{ getColorName(color) + " Number Card " + std::to_string(number) , color}, Number{number}
{}