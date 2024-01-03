#pragma once
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

enum class ETurnFlow : uint8_t;
class Card;
class DeckController;
class Player;

class Round : public Entity
{
protected:
    int RoundIndex;
    
    void DrawTurn(const EntityPtr<Player>& player, const EntityPtr<DeckController>& deckController, const ETurnFlow& turnFlow) const;

public:
    Round(int index);

    virtual void RunRound(const EntityPtr<Player>& currentPlayer, const EntityPtr<DeckController>& deckController, ETurnFlow turnFlow);
};
