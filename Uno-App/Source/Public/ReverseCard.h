#pragma once
#include "Card.h"
#include "IPostRoundAction.h"

class ReverseCard : public Card, public IPostRoundAction
{
public:
    ReverseCard(EColor color);
    std::string GetCardTypeName() const override;
    [[nodiscard]] bool CanTossCardOnMe(const EntityPtr<Card>& other) const override;
    void Execute(Match* currentMatch) override;
};
