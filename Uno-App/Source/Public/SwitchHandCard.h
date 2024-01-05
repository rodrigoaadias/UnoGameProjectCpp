#pragma once
#include "Card.h"
#include "IPostRoundAction.h"

class SwitchHandCard : public Card, public IPostRoundAction
{
public:
    SwitchHandCard();
    std::string GetCardTypeName() const override;
    void Execute(IMatchContext* currentMatch) override;
};
