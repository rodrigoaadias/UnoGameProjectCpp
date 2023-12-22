#pragma once
#include "Round.h"

class MustBuyRound : public Round
{
    int AmountToBuy{0};
    void BuyCumulatedCards(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController);
public:
    MustBuyRound(int index, int amountToBuy);

    void RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController, const ETurnFlow& turnFlow) override;
};
