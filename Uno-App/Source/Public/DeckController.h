#pragma once
#include <stack>
#include <vector>
#include "Core/Public/Entity.h"
#include "Core/EntityPtr.h"

enum class EColor : uint8_t;
class Card;

class DeckController : public Entity
{
    std::vector<EntityPtr<Card>> AllCards;
    std::stack<EntityPtr<Card>> TossedCards;
    std::stack<EntityPtr<Card>> CardsOnDeck;

    void CreateCards();
    void CreateNumberCardInAllColors(int number);
    void CreateNumberCardOfColor(int number, EColor color);
public:
    DeckController(const std::string& name);

    void ShuffleDeckCards();
    void AddCardToDeck(EntityPtr<Card> card);
    bool IsDeckEmpty();
    void ShuffleTossedCardsBackToDeck();
    std::weak_ptr<Card> GetTopCard();
};
