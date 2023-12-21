#pragma once
#include "Card.h"
#include "IPostRoundAction.h"

class ReverseCard : public Card, public IPostRoundAction
{
public:
    ReverseCard(const EColor& color);
    std::string GetCardTypeName() const override;
    bool CanTossCardOnMe(EntityPtr<Card> other) override;
    void Execute(Match* currentMatch) override;
};
