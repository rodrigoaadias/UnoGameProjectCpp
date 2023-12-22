#include "Public/DeckController.h"
#include <chrono>
#include <random>
#include "Core/Core.h"
#include "Core/Public/Engine.h"
#include "Public/JumpCard.h"
#include "Public/MustBuyCard.h"
#include "Public/NumberCard.h"
#include "Public/ReverseCard.h"
#include "Public/SwitchHandCard.h"

DeckController::DeckController(const std::string& name)
    : Entity{name}
{
    AllCards.reserve(104);
    DeckCards.reserve(104);
    CreateCards();
}

void DeckController::CreateCards()
{
    for (int i=0; i < 10; i++)
    {
        CreateNumberCardInAllColors(i);
    }

    CreateSpecialCardsByColor(EColor::Blue);
    CreateSpecialCardsByColor(EColor::Red);
    CreateSpecialCardsByColor(EColor::Green);
    CreateSpecialCardsByColor(EColor::Yellow);

    CreateExtraCards();

    Core::LogMessage("Cards created! Total of cards available: " + std::to_string(AllCards.size()));
}

void DeckController::CreateNumberCardInAllColors(const int number)
{
    CreateNumberCardOfColor(number, EColor::Blue);
    CreateNumberCardOfColor(number, EColor::Yellow);
    CreateNumberCardOfColor(number, EColor::Red);
    CreateNumberCardOfColor(number, EColor::Green);
}

void DeckController::CreateNumberCardOfColor(const int number, EColor color)
{
    EntityPtr<NumberCard> card01 = EntityPtr<NumberCard>::MakeEntityPtr(color, number);
    EntityPtr<NumberCard> card02 = EntityPtr<NumberCard>::MakeEntityPtr(color, number);
    EmplaceCreatedCard(static_cast<EntityPtr<Card>>(card01));
    EmplaceCreatedCard(static_cast<EntityPtr<Card>>(card02));
}

void DeckController::CreateSpecialCardsByColor(EColor color)
{
    for (int i=0; i < 2; i++)
    {
        EntityPtr<MustBuyCard> plusTwoCard = EntityPtr<MustBuyCard>::MakeEntityPtr(color, 2);
        EntityPtr<JumpCard> jumpCard = EntityPtr<JumpCard>::MakeEntityPtr(color);
        EntityPtr<ReverseCard> reverseCard = EntityPtr<ReverseCard>::MakeEntityPtr(color);

        EmplaceCreatedCard(static_cast<EntityPtr<Card>>(plusTwoCard));
        EmplaceCreatedCard(static_cast<EntityPtr<Card>>(jumpCard));
        EmplaceCreatedCard(static_cast<EntityPtr<Card>>(reverseCard));
    }
}

void DeckController::CreateExtraCards()
{
    for (int i=0; i < 4; i++)
    {
        const EntityPtr<Card> switchHandCard = static_cast<EntityPtr<Card>>(EntityPtr<SwitchHandCard>::MakeEntityPtr());
        EmplaceCreatedCard(switchHandCard);
    }
}

void DeckController::EmplaceCreatedCard(EntityPtr<Card> card)
{    
    AllCards.emplace_back(card);
    AddCardToDeck(card);
}

EntityPtr<Card> DeckController::PopFromStack()
{
    if(TossedCards.empty())
    {
        return {};
    }

    auto topCard = TossedCards.top();
    TossedCards.pop();
    return topCard;
}

void DeckController::ShuffleDeckCards()
{
    const unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::ranges::shuffle(DeckCards, std::default_random_engine(seed));

    CreateExtraCards();
}

void DeckController::AddCardToDeck(EntityPtr<Card>& card)
{
    DeckCards.emplace_back(card);
}

bool DeckController::IsDeckEmpty() const
{
    return DeckCards.empty();
}

void DeckController::ShuffleTossedCardsBackToDeck()
{
    while (!TossedCards.empty())
    {
        DeckCards.emplace_back(PopFromStack());
    }

    ShuffleDeckCards();
}

void DeckController::AddCardToTable(const EntityPtr<Card>& card)
{
    TossedCards.emplace(card);
}

EntityPtr<Card> DeckController::BuyCardFromDeck()
{
    if(DeckCards.empty())
    {
        const EntityPtr<Card> lastTossedCard = PopFromStack();
        ShuffleTossedCardsBackToDeck();
        AddCardToTable(lastTossedCard);
    }

    auto topCard = DeckCards.back();
    DeckCards.pop_back();

    return topCard;
}

EntityPtr<Card> DeckController::GetLastTossedCard()
{
    return TossedCards.empty() ? EntityPtr<Card>() : TossedCards.top();
}

int DeckController::GetAmountOfDeckCards() const
{
    return static_cast<int>(DeckCards.size());
}

int DeckController::GetAmountOfTossedCards() const
{
    return static_cast<int>(TossedCards.size());    
}