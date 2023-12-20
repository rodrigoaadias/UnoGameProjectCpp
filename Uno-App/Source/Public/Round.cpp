#include "Round.h"
#include "Public/DeckController.h"
#include "Card.h"
#include "Player.h"
#include "Statics.h"
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

void Round::AddToLineIndex(std::vector<std::string>& lines, const std::string& text, int i)
{
    if(static_cast<int>(lines.size()) <= i)
    {               
        lines.emplace_back(text);
    }
    else
    {
        lines[i].append(text);
    }
}

void Round::DrawCards(const std::vector<EntityPtr<Card>>& cards, bool drawOption)
{
    std::vector<std::string> lines;
    const int startAdding = drawOption ? 1 : 0;
    lines.reserve(COLUMN_HEIGHT + startAdding);

    int currentCard = -1;
    for (const EntityPtr<Card>& card : cards)
    {
        currentCard++;
        if(!card.IsValid())
        {
            continue;
        }

        std::string spaceBetweenCards = "      ";
        std::vector<std::string> cardDisplay = Card::GetDisplayCard(**card.Instance);
        if(drawOption)
        {
            AddToLineIndex(lines, "  Option: " + std::to_string(currentCard) + spaceBetweenCards, 0);
        }

        for (int i=0; i < COLUMN_HEIGHT; i++)
        {
            AddToLineIndex(lines, cardDisplay[i] + spaceBetweenCards, i+startAdding);
        }
    }

    for (const std::string& line : lines)
    {
        Core::LogMessage(line + DEFAULT_COLOR);
    }
}

void Round::DrawTurn(EntityPtr<Player> player, EntityPtr<DeckController> deckController)
{
    system("cls");
    Core::LogMessage("ROUND " + std::to_string(RoundIndex) + ": " + player->GetDisplayName() + "'s turn!");

    const auto tableCard = deckController->GetLastTossedCard();
    if(tableCard.IsValid())
    {
        Core::LogMessage("Card on table:");
        DrawCards(std::vector {tableCard});
    }
    else
    {
        Core::LogMessage("There is no card on the table");        
    }

    std::cout << "\n\n\n";
    Core::LogMessage(player->GetName() + " - your current cards: ");

    DrawCards(player->GetCards(), true);
    std::cout << "\n";
}