#pragma once
#include "Round.h"

class JumpRound : public Round
{
public:
    JumpRound(int index);

    void RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController, const ETurnFlow& turnFlow) override;
};
