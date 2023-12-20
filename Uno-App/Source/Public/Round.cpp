#include "Round.h"
#include "Public/DeckController.h"
#include "Card.h"
#include "ETurnFlow.h"
#include "Player.h"
#include "Core/Core.h"

std::string Round::GetFlowName(const ETurnFlow& flow) const
{
    switch (flow)
    {
    case ETurnFlow::Clockwise:
        return  "Clockwise";
    case ETurnFlow::AntiClockwise:
        return "Anti-clockwise";
    }

    return "Invalid flow";
}

Round::Round(int index)
    :Entity{"Round " + std::to_string(index)}, RoundIndex{index}
{}

void Round::RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController, const ETurnFlow& turnFlow)
{
    DrawTurn(currentPlayer, deckController, turnFlow);

    currentPlayer->PlayTurn(deckController.get());
}

void Round::DrawTurn(EntityPtr<Player> player, EntityPtr<DeckController> deckController, const ETurnFlow& turnFlow) const
{
    system("cls");
    Core::LogMessage("ROUND " + std::to_string(RoundIndex) + ": " + player->GetDisplayName() + "'s turn!");
    Core::LogMessage("Flow: " + GetFlowName(turnFlow));
    Core::LogMessage("Cards on Deck: " + std::to_string(deckController->GetAmountOfDeckCards()));

    const auto tableCard = deckController->GetLastTossedCard();
    if(tableCard.IsValid())
    {
        Core::LogMessage("Card on table:");
        Card::DrawCards(std::vector {tableCard});
    }
    else
    {
        Core::LogMessage("There is no card on the table");        
    }

    std::cout << "\n\n\n";
    Core::LogMessage(player->GetName() + " - your current cards: ");

    Card::DrawCards(player->GetCards(), true);
    std::cout << "\n";
}