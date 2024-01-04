#pragma once
#include "Card.h"
#include "Core/EntityPtr.h"

class NumberCard : public Card
{
    int Number;
public:
    NumberCard(EColor color, int number);

    [[nodiscard]] int GetNumber() const { return Number; }
    [[nodiscard]] std::string GetCardTypeName() const override;
    [[nodiscard]] bool CanTossCardOnMe(const EntityPtr<Card>& other) const override;
};
