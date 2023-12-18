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
    std::vector<std::weak_ptr<Card>> DeckCards;
    std::stack<std::weak_ptr<Card>> TossedCards;

    void CreateCards();
    void CreateNumberCardInAllColors(int number);
    void CreateNumberCardOfColor(int number, EColor color);
    void CreateSpecialCardsByColor(EColor color);
    void EmplaceCreatedCard(EntityPtr<Card> card);
public:
    DeckController(const std::string& name);

    void ShuffleDeckCards();
    void AddCardToDeck(EntityPtr<Card>& card);
    bool IsDeckEmpty() const;
    void ShuffleTossedCardsBackToDeck();
    std::weak_ptr<Card> GetCardFromDeck();
    std::weak_ptr<Card> GetLastTossedCard();
};
