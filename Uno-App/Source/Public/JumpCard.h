#pragma once
#include "Card.h"
#include "ICustomRoundCard.h"

class JumpCard : public Card, public ICustomRoundCard
{
public:
    JumpCard(EColor color);
    
    EntityPtr<Round> GenerateCustomRound(int roundIndex) override;

    [[nodiscard]] std::string GetCardTypeName() const override;
    [[nodiscard]] bool CanTossCardOnMe(const EntityPtr<Card>& other) const override;
};