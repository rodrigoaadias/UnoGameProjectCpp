#pragma once
#include "Card.h"
#include "ICustomRoundCard.h"

class JumpCard : public Card, public ICustomRoundCard
{
public:
    JumpCard(const EColor& color);
    std::string GetCardTypeName() const override;

    EntityPtr<Round> GetCustomRound(int roundIndex) override;
    
    bool CanBeTossed(EntityPtr<Card> other) override;
};
