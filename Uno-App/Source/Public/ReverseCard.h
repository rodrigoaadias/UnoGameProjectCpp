#pragma once
#include "Card.h"

class ReverseCard : public Card
{
public:
    ReverseCard(const EColor& color);
    std::string GetCardTypeName() const override;
};
