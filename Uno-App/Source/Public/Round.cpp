#include "Round.h"
#include "Public/DeckController.h"
#include "Card.h"
#include "Player.h"
#include "Core/Core.h"

Round::Round(int index)
    :Entity{"Round " + std::to_string(index)}, RoundIndex{index}
{}

bool Round::RunRound(EntityPtr<Player> currentPlayer, EntityPtr<DeckController>& deckController)
{
    DrawTurn(currentPlayer, deckController);

    currentPlayer->PlayTurn(deckController.get());

    return true;
}

void Round::DrawTurn(EntityPtr<Player> player, EntityPtr<DeckController> deckController)
{
    system("cls");
    Core::LogMessage("ROUND " + std::to_string(RoundIndex) + ": " + player->GetDisplayName() + "'s turn!");

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