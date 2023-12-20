#pragma once
#include <stack>
#include <vector>
#include "EColor.h"
#include "Core/Public/Entity.h"
#include "Core/EntityPtr.h"

class Card;

class DeckController : public Entity
{
    std::vector<EntityPtr<Card>> AllCards;
    std::vector<EntityPtr<Card>> DeckCards;
    std::stack<EntityPtr<Card>> TossedCards;

    void CreateCards();
    void CreateNumberCardInAllColors(int number);
    void CreateNumberCardOfColor(int number, EColor color);
    void CreateSpecialCardsByColor(EColor color);
    void EmplaceCreatedCard(EntityPtr<Card> card);
    EntityPtr<Card> PopFromStack();
public:
    DeckController(const std::string& name);

    void ShuffleDeckCards();
    void AddCardToDeck(EntityPtr<Card>& card);
    bool IsDeckEmpty() const;
    void ShuffleTossedCardsBackToDeck();
    void AddCardToTable(const EntityPtr<Card>& card);
    EntityPtr<Card> BuyCardFromDeck();
    EntityPtr<Card> GetLastTossedCard();
};
