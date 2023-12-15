#include "Public/DeckController.h"

#include "Core/Public/Engine.h"
#include "Public/NumberCard.h"

DeckController::DeckController(const std::string& name)
    : Entity{name}
{
    CreateCards();
}

void DeckController::CreateCards()
{
    AllCards.reserve(104);
    for (int i=0; i < 10; i++)
    {
        CreateNumberCardInAllColors(i);
    }

    std::cout << "Deck amount: " << AllCards.size() << std::endl;
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
    EntityPtr<NumberCard> card01 = Engine::CreateEntity<NumberCard>(color, number);
    EntityPtr<NumberCard> card02 = Engine::CreateEntity<NumberCard>(color, number);
    AllCards.push_back(static_cast<EntityPtr<Card>>(card01));
    AllCards.push_back(static_cast<EntityPtr<Card>>(card02));
}

void DeckController::ShuffleDeckCards()
{}

void DeckController::AddCardToDeck(EntityPtr<Card> card)
{}

bool DeckController::IsDeckEmpty()
{
    return false;
}

void DeckController::ShuffleTossedCardsBackToDeck()
{}

std::weak_ptr<Card> DeckController::GetTopCard()
{
    return TossedCards.empty() ? std::weak_ptr<Card>() : TossedCards.top().get();
}