#pragma once
#include "Round.h"

class MustBuyRound : public Round
{
    int AmountToBuy{0};
    void BuyCumulatedCards(const EntityPtr<Player>& currentPlayer, const EntityPtr<DeckController>& deckController) const;
public:
    MustBuyRound(int index, int amountToBuy);

    void RunRound(const EntityPtr<Player>& currentPlayer, const EntityPtr<DeckController>& deckController, ETurnFlow turnFlow) override;
};