#include "Public/Match.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"
#include "Public/DeckController.h"
#include "Public/Player.h"
#include "Public/ICustomRoundCard.h"
#include "Public/Round.h"

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
    Core::LogMessage("Starting Match: " + GetName());
    PlayersCount = GetNumberOfPlayers();
    JoinPlayers(PlayersCount);
    CreateDeck();
    SortCardsToPlayers();
    SetupTurnFlow();

    bMatchReady = true;
}

int Match::GetNumberOfPlayers()
{
    int numPlayers = Core::GetInput<int>("How many players will join this match? (Must be between 2 and 10): ");
    while (numPlayers < 2 || numPlayers > 10)
    {
        Core::LogMessage(std::to_string(numPlayers) + " players are not allowed. Select a number between 2 and 10");
        numPlayers = Core::GetInput<int>("How many players will join this match? (Must be between 2 and 10): ");
    }

    return numPlayers;
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

    for (auto player : JoinedPlayers)
    {
        for (int i=0; i < INITIAL_CARDS_PER_PLAYER; i++)
        {
            player->BuyDeckCard(Deck.get());
        }
    }
}

void Match::SetupTurnFlow()
{
    CurrentPlayerIndex = Core::RandomRange(0, PlayersCount - 1);
    Flow = Core::RandomRange(0, 1) == 0 ? ETurnFlow::Clockwise : ETurnFlow::AntiClockwise;
}

void Match::IncreaseTurn()
{
    CurrentTurn++;
    CurrentPlayerIndex += Flow == ETurnFlow::Clockwise ? 1 : -1;
    
    if(CurrentPlayerIndex >= static_cast<int>(JoinedPlayers.size()))
    {
        CurrentPlayerIndex = 0;
    }

    if(CurrentPlayerIndex < 0)
    {
        CurrentPlayerIndex = static_cast<int>(JoinedPlayers.size()) - 1;
    }
}

void Match::PlayTurn()
{
    const auto currentPlayerTurn = JoinedPlayers[CurrentPlayerIndex];
    EntityPtr<Round> newRound;

    // execute pre turn actions
    const auto tossedCard = Deck->GetLastTossedCard();
    if(tossedCard.IsValid() && tossedCard != LastCard)
    {
        const auto customRoundCard = std::dynamic_pointer_cast<ICustomRoundCard>(*tossedCard.Instance);
        if (customRoundCard != nullptr)
        {
            newRound = customRoundCard->GetCustomRound(CurrentTurn);
        }
    }

    // Run turn
    if(!newRound.IsValid())
    {
        newRound = EntityPtr<Round>::MakeEntityPtr(CurrentTurn);
    }

    LastCard = tossedCard;
    newRound->RunRound(currentPlayerTurn, Deck, Flow);

    if(currentPlayerTurn->GetCards().empty())
    {
        Core::WaitAnyKey("CONGRATULATIONS " + currentPlayerTurn->GetName() + "!!! You won the game!");
        FinishMatch();
        return;
    }

    IncreaseTurn();

    Core::WaitAnyKey("Press any key to go to next turn");
}

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