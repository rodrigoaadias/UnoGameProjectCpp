#pragma once
#include <vector>

#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Card;
class DeckController;
class Player;

class Round : public Entity
{
    int RoundIndex;
    
    void DrawCards(const std::vector<EntityPtr<Card>>& cards, bool drawOption = false);
    void DrawTurn(EntityPtr<Player> player, EntityPtr<DeckController> deckController);
public:
    Round(int index);

    bool RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController);
    void AddToLineIndex(std::vector<std::string>& lines, const std::string& text, int i);
};
