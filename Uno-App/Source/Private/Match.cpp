#include "Public/Match.h"
#include "Statics.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"
#include "Public/DeckController.h"
#include "Public/Player.h"
#include <stdlib.h>

Match::Match(const std::string& matchName)
    : Entity{matchName}, CurrentTurn{0}, Flow{ETurnFlow::Clockwise}
{
    JoinedPlayers.reserve(10);
}

void Match::Begin()
{
    Entity::Begin();
    StartNewMatch();
}

void Match::Tick()
{
    Entity::Tick();

    if(bMatchReady && !IsMatchEnded())
    {
        PlayTurn();
    }
}

void Match::StartNewMatch()
{
    Core::LogMessage("Starting Match " + GetName());
    int numPlayers = Core::GetInput<int>("How many players will join this match? (Must be between 2 and 10): ");
    while (numPlayers < 2 || numPlayers > 10)
    {
        Core::LogMessage(std::to_string(numPlayers) + " players are not allowed. Select a number between 2 and 10");
        numPlayers = Core::GetInput<int>("How many players will join this match? (Must be between 2 and 10): ");
    }

    JoinPlayers(numPlayers);
    CreateDeck();
    SortCardsToPlayers();
    SetupTurnFlow();

    bMatchReady = true;
}

void Match::JoinPlayers(const int& number)
{
    PlayersCount = number;
    for (int i=0; i < number; i++)
    {
        JoinedPlayers.emplace_back(CreatePlayer(i));
    }
}

EntityPtr<Player> Match::CreatePlayer(const int& index)
{
    const auto playerName = Core::GetInput<std::string>("Player " + std::to_string(index) + ": What's your name? ");
    for (EntityPtr<Player> current : JoinedPlayers)
    {
        if(current->GetName() == playerName)
        {
            Core::LogMessage("You can't assign your name as " + playerName + " because another player already has this name");
            return CreatePlayer(index);
        }
    }

    return EntityPtr<Player>::MakeEntityPtr(playerName, index);
}

void Match::CreateDeck()
{
    Deck = EntityPtr<DeckController>::MakeEntityPtr("Deck Controller");
}

void Match::SortCardsToPlayers()
{
    Deck->ShuffleDeckCards();

    for (auto player : JoinedPlayers)
    {
        for (int i=0; i < 7; i++)
        {
            player->AddCardToHand(Deck->BuyCardFromDeck());
        }
    }
}

void Match::SetupTurnFlow()
{
    CurrentPlayerIndex = rand() % PlayersCount;
    Flow = rand() % 2 == 0 ? ETurnFlow::Clockwise : ETurnFlow::AntiClockwise;
}

void Match::PlayTurn()
{
    const std::weak_ptr<Player> currentPlayerTurn = JoinedPlayers[CurrentPlayerIndex].get();

    // execute pre turn actions

    // draw turn infos
    DrawTurn(currentPlayerTurn);

    Core::LogMessage(currentPlayerTurn.lock()->GetName() + ": what is your choice?");
    Core::LogMessage("1 - Play a card");
    Core::LogMessage("2 - Quit Game");

    const int choice = Core::GetInput<int>({});
    if(choice == 2)
    {
        FinishMatch();
    }

    //execute post turn actions

    // select next player
}

void Match::ExecuteCardAction()
{}

void Match::ExecuteCardTossAction()
{}

void Match::SkipTurn()
{}

void Match::ReverseFlow()
{}

bool Match::IsMatchEnded()
{
    return bMatchFinished;
}

void Match::FinishMatch()
{
    bMatchFinished = true;
}

void Match::DrawCards(const std::vector<std::weak_ptr<Card>>& cards)
{
    std::vector<std::string> lines;
    lines.reserve(COLUMN_HEIGHT);
    for (const std::weak_ptr<Card>& card : cards)
    {
        if(card.expired())
        {
            continue;
        }

        std::string spaceBetweenCards = "      ";
        std::vector<std::string> cardDisplay = Card::GetDisplayCard(*std::dynamic_pointer_cast<Card>(card.lock()));
        for (int i=0; i < COLUMN_HEIGHT; i++)
        {
            if(static_cast<int>(lines.size()) <= i)
            {               
                lines.emplace_back(cardDisplay[i] + spaceBetweenCards);
            }
            else
            {
                lines[i].append(cardDisplay[i] + spaceBetweenCards);
            }
        }
    }

    for (const std::string& line : lines)
    {
        Core::LogMessage(line + DEFAULT_COLOR);
    }
}

void Match::DrawTurn(std::weak_ptr<Player> player)
{
    system("cls");
    const auto playerPtr = player.lock();
    Core::LogMessage("ROUND " + std::to_string(CurrentTurn) + ": " + playerPtr->GetDisplayName() + "'s turn!");

    const auto tableCard = Deck->GetLastTossedCard();
    if(tableCard.expired())
    {
        Core::LogMessage("There is no card on the table");        
    }
    else
    {
        Core::LogMessage("Card on table:");
        DrawCards(std::vector {tableCard});
    }

    std::cout << "\n\n\n";
    Core::LogMessage(playerPtr->GetName() + " - your current cards: ");
    DrawCards(playerPtr->GetCards());
    std::cout << "\n";
}