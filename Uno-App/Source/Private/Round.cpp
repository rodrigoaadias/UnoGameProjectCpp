#include "Public/Round.h"
#include "Public/DeckController.h"
#include "Public/Card.h"
#include "Public/Player.h"
#include "Core/Core.h"
#include "Public/CardPrinter.h"
#include <sstream>

Round::Round(const int index)
    :Entity{"Round " + std::to_string(index)}, RoundIndex{index}
{}

void Round::RunRound(const EntityPtr<Player>& currentPlayer, const EntityPtr<DeckController>& deckController, const std::string_view turnFlowName)
{
    DrawTurn(currentPlayer, deckController, turnFlowName);

    currentPlayer->PlayTurn(deckController.GetWeakPtr());
}

void Round::DrawTurn(const EntityPtr<Player>& player, const EntityPtr<DeckController>& deckController, const std::string_view turnFlowName) const
{
    Core::ClearConsole();
    Core::LogMessage("ROUND " + std::to_string(RoundIndex) + ": " + player->GetDisplayName() + "'s turn!");
    std::stringstream flowStream;
    flowStream << "Flow: " << turnFlowName;
    Core::LogMessage(flowStream.str());
    Core::LogMessage("Cards on Deck: " + std::to_string(deckController->GetAmountOfDeckCards()));

    const EntityPtr<Card>& tableCard = deckController->GetLastTossedCard();
    if(tableCard.IsValid())
    {
        Core::LogMessage("Card on table:");

        std::vector<EntityPtr<Card>> cards;
        cards.emplace_back(tableCard);

        CardPrinter::DrawCards(cards);
    }
    else
    {
        Core::LogMessage("There is no card on the table");        
    }

    std::cout << "\n\n\n";
    Core::LogMessage(player->GetName() + " - your current cards: ");

    CardPrinter::DrawCards(player->GetCards(), true);
    std::cout << "\n";
}