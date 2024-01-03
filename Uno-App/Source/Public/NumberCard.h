#pragma once
#include "Card.h"
#include "Core/EntityPtr.h"

class NumberCard : public Card
{
    int Number;
public:
    NumberCard(EColor color, int number);

    int GetNumber() const { return Number; }
    std::string GetCardTypeName() const override;
    bool CanTossCardOnMe(const EntityPtr<Card>& other) const override;
};
