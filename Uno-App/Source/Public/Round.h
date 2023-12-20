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
    
    void DrawTurn(EntityPtr<Player> player, EntityPtr<DeckController> deckController, const ETurnFlow& turnFlow) const;

private:
    std::string GetFlowName(const ETurnFlow& flow) const;

public:
    Round(int index);

    virtual void RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController, const ETurnFlow& turnFlow);
};
