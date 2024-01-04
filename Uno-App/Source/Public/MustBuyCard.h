#pragma once
#include "Card.h"
#include "ICustomRoundCard.h"

class MustBuyCard : public Card, public ICustomRoundCard
{
    int AmountToBuy;
    int Cumulated{0};
    bool IsInRound{false};

public:
    MustBuyCard(EColor color, int amountToBuy);
    
    [[nodiscard]] int GetAmountToBuy() const;
    [[nodiscard]] std::string GetCardTypeName() const override;
    [[nodiscard]] bool CanTossCardOnMe(const EntityPtr<Card>& other) const override;
    EntityPtr<Round> GenerateCustomRound(int roundIndex) override;

    void Cumulate(int amount);
    void ClearRound();
};
