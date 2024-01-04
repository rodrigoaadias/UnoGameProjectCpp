#pragma once
#include "Round.h"

class JumpRound : public Round
{
public:
    JumpRound(int index);

    void RunRound(const EntityPtr<Player>& currentPlayer, const EntityPtr<DeckController>& deckController, std::string_view turnFlowName) override;
};
