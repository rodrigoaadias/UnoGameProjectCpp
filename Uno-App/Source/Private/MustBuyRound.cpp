#include "Public/MustBuyRound.h"
#include "Public/DeckController.h"
#include "Public/MustBuyCard.h"
#include "Public/Player.h"
#include "Core/Core.h"

MustBuyRound::MustBuyRound(const int index, const int amountToBuy)
    :Round{index}, AmountToBuy{amountToBuy}
{}

void MustBuyRound::BuyCumulatedCards(const EntityPtr<Player>& currentPlayer, const EntityPtr<DeckController>& deckController)
{
    Core::WaitAnyKey(currentPlayer->GetName() + ": you must buy " + std::to_string(AmountToBuy) + " cards.");
    std::vector<EntityPtr<Card>> cardsToDraw;
    cardsToDraw.reserve(AmountToBuy);
    for (int i=0; i < AmountToBuy; i++)
    {
        currentPlayer->BuyDeckCard(deckController.GetWeakPtr());
        cardsToDraw.emplace_back(currentPlayer->GetCards().back());
    }

    Core::LogMessage(currentPlayer->GetName() + " has bought the following cards: ");
    Card::DrawCards(cardsToDraw);
}

void MustBuyRound::RunRound(const EntityPtr<Player>& currentPlayer, const EntityPtr<DeckController>& deckController, ETurnFlow turnFlow)
{
    DrawTurn(currentPlayer, deckController, turnFlow);
    EntityPtr<Card> cardOnTable = deckController->GetLastTossedCard();
    if(currentPlayer->CanTossCard(cardOnTable))
    {
        currentPlayer->PlayTurn(deckController.GetWeakPtr());
        EntityPtr<MustBuyCard> newMustBuy = static_cast<EntityPtr<MustBuyCard>>(deckController->GetLastTossedCard());
        newMustBuy->Cumulate(AmountToBuy);
    }
    else
    {
        BuyCumulatedCards(currentPlayer, deckController);
    }

    
    EntityPtr<MustBuyCard> lastCard = static_cast<EntityPtr<MustBuyCard>>(cardOnTable);
    if(lastCard.IsValid())
    {
        lastCard->ClearRound();
    }
}