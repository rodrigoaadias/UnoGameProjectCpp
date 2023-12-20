#pragma once
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Card;
class DeckController;
class Player;

class Round : public Entity
{
    int RoundIndex;
    
    void DrawTurn(EntityPtr<Player> player, EntityPtr<DeckController> deckController);
public:
    Round(int index);

    bool RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController);
};
