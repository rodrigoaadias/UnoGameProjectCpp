#pragma once
#include "Card.h"

class JumpCard : public Card
{
public:
    JumpCard(const EColor& color);
    std::string GetCardTypeName() const override;
};
