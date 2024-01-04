#pragma once
#include <stack>
#include <vector>
#include "EColor.h"
#include "Core/Public/Entity.h"
#include "Core/EntityPtr.h"

class Card;

class DeckController : public Entity
{
    inline static constexpr int CARDS_AMOUNT_CAPACITY = 104;
    inline static constexpr int NUMBER_CARDS_AMOUNT = 10;
    inline static constexpr int SPECIAL_CARDS_BY_COLOR_AMOUNT = 2;
    inline static constexpr int EXTRA_CARD_AMOUNT = 4;
    EntityPtr<Card> EmptyCard{};

    std::vector<EntityPtr<Card>> AllCards;
    std::vector<EntityPtr<Card>> DeckCards;
    std::stack<EntityPtr<Card>> TossedCards;

    void CreateCards();
    void CreateNumberCardInAllColors(int number);
    void CreateNumberCardOfColor(int number, EColor color);
    void CreateSpecialCardsByColor(EColor color);
    void CreateExtraCards();
    void EmplaceCreatedCard(const EntityPtr<Card>& card);
    const EntityPtr<Card>& PopFromStack();
public:
    DeckController(const std::string& name);

    void ShuffleDeckCards();
    void AddCardToDeck(EntityPtr<Card> card);
    [[nodiscard]] bool IsDeckEmpty() const;
    void ShuffleTossedCardsBackToDeck();
    void AddCardToTable(EntityPtr<Card> card);
    EntityPtr<Card> BuyCardFromDeck();

    [[nodiscard]] const EntityPtr<Card>& GetLastTossedCard() const;
    [[nodiscard]] int GetAmountOfDeckCards() const;
    [[nodiscard]] int GetAmountOfTossedCards() const;
};
