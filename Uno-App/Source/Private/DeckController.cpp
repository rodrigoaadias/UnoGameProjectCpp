#include "Public/DeckController.h"
#include <chrono>
#include <random>
#include "Core/Core.h"
#include "Core/Public/Engine.h"
#include "Public/JumpCard.h"
#include "Public/MustBuyCard.h"
#include "Public/NumberCard.h"
#include "Public/ReverseCard.h"

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

    Core::LogMessage("Cards created! Total of cards available: " + std::to_string(AllCards.size()));
}

void DeckController::CreateNumberCardInAllColors(int number)
{
    CreateNumberCardOfColor(number, EColor::Blue);
    CreateNumberCardOfColor(number, EColor::Yellow);
    CreateNumberCardOfColor(number, EColor::Red);
    CreateNumberCardOfColor(number, EColor::Green);
}

void DeckController::CreateNumberCardOfColor(int number, EColor color)
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

void DeckController::EmplaceCreatedCard(EntityPtr<Card> card)
{    
    AllCards.emplace_back(card);
    AddCardToDeck(card);
}

void DeckController::ShuffleDeckCards()
{
    const unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
    std::ranges::shuffle(DeckCards, std::default_random_engine(seed));
}

void DeckController::AddCardToDeck(EntityPtr<Card>& card)
{
    DeckCards.emplace_back(card.get());
}

bool DeckController::IsDeckEmpty() const
{
    return DeckCards.empty();
}

void DeckController::ShuffleTossedCardsBackToDeck()
{}

std::weak_ptr<Card> DeckController::BuyCardFromDeck()
{
    if(DeckCards.empty())
    {
        ShuffleTossedCardsBackToDeck();
    }

    auto topCard = DeckCards.back();
    DeckCards.pop_back();

    return topCard;
}

std::weak_ptr<Card> DeckController::GetLastTossedCard()
{
    return TossedCards.empty() ? std::weak_ptr<Card>() : TossedCards.top();
}