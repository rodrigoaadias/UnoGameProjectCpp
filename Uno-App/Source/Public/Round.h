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
    
    void DrawTurn(EntityPtr<Player> player, EntityPtr<DeckController> deckController) const;
public:
    Round(int index);

    virtual void RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController);
};
