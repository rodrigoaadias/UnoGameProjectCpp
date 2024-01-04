#pragma once
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Card;
class DeckController;
class Player;

class Round : public Entity
{
protected:
    int RoundIndex;
    
    void DrawTurn(const EntityPtr<Player>& player, const EntityPtr<DeckController>& deckController, std::string_view turnFlowName) const;

public:
    Round(int index);

    virtual void RunRound(const EntityPtr<Player>& currentPlayer, const EntityPtr<DeckController>& deckController, std::string_view turnFlowName);
};
