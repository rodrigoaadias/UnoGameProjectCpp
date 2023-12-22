#include "MustBuyRound.h"
#include "DeckController.h"
#include "MustBuyCard.h"
#include "Player.h"
#include "Core/Core.h"

MustBuyRound::MustBuyRound(const int index, const int amountToBuy)
    :Round{index}, AmountToBuy{amountToBuy}
{}

void MustBuyRound::BuyCumulatedCards(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController)
{
    Core::WaitAnyKey(currentPlayer->GetName() + ": you must buy " + std::to_string(AmountToBuy) + " cards.");
    std::vector<EntityPtr<Card>> cardsToDraw;
    cardsToDraw.reserve(AmountToBuy);
    for (int i=0; i < AmountToBuy; i++)
    {
        currentPlayer->BuyDeckCard(deckController.get());
        cardsToDraw.emplace_back(currentPlayer->GetCards().back());
    }

    Core::LogMessage(currentPlayer->GetName() + " has bought the following cards: ");
    Card::DrawCards(cardsToDraw);
}

void MustBuyRound::RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController,
                            const ETurnFlow& turnFlow)
{
    DrawTurn(currentPlayer, deckController, turnFlow);
    EntityPtr<Card> cardOnTable = deckController->GetLastTossedCard();
    if(currentPlayer->CanTossCard(cardOnTable))
    {
        currentPlayer->PlayTurn(deckController.get());
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