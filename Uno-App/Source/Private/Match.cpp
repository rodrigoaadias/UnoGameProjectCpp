#include "Public/Match.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"
#include "Public/DeckController.h"
#include "Public/Player.h"

Match::Match(const std::string& matchName)
    : Entity{matchName}, CurrentTurn{0}, Flow{ETurnFlow::Clockwise}
{ }

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
}

void Match::JoinPlayers(const int& number)
{
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
}

void Match::SortFirstPlayerTurn()
{}

void Match::PlayTurn()
{}

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
    return false;
}

void Match::FinishMatch()
{}