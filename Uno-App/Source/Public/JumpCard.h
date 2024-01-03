#pragma once
#include "Card.h"
#include "ICustomRoundCard.h"

class JumpCard : public Card, public ICustomRoundCard
{
public:
    JumpCard(const EColor& color);
    std::string GetCardTypeName() const override;

    EntityPtr<Round> GenerateCustomRound(int roundIndex) override;
    
    bool CanTossCardOnMe(const EntityPtr<Card>& other) const override;
};
