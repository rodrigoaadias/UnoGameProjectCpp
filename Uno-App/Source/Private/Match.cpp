#include "Public/Match.h"
#include "Core/Core.h"
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
}

void Match::JoinPlayers(int number)
{
    for (int i=0; i < number; i++)
    {
        JoinedPlayers.push_back(CreatePlayer(i));
    }
}

EntityPtr<Player> Match::CreatePlayer(int index)
{
    std::string playerName = Core::GetInput<std::string>("Player " + std::to_string(index) + ": What's your name? ");
    return EntityPtr<Player>::MakeEntityPtr(playerName);
}

void Match::CreateDeck()
{}

void Match::SortCardsToPlayers()
{}

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