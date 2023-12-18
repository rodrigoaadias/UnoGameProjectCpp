#include "Public/NumberCard.h"

NumberCard::NumberCard(const EColor color, const int number)
    : Card{ "Number Card " + std::to_string(number) , color}, Number{number}
{}