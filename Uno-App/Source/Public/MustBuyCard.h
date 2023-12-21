#pragma once
#include "Card.h"
#include "ICustomRoundCard.h"
#include "IPostRoundAction.h"

class MustBuyCard : public Card, public ICustomRoundCard
{
    int AmountToBuy;
    int Cumulated{0};
    bool IsInRound{false};

public:
    MustBuyCard(const EColor& color, int amountToBuy);

    int GetAmountToBuy() const;
    void Cumulate(int amount);

    std::string GetCardTypeName() const override;
    bool CanTossCardOnMe(EntityPtr<Card> other) override;
    EntityPtr<Round> GetCustomRound(int roundIndex) override;
    void ClearRound();
};
