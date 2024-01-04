#include "Public/Match.h"

#include "Statics.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"
#include "Public/DeckController.h"
#include "Public/Player.h"
#include "Public/ICustomRoundCard.h"
#include "Public/Round.h"
#include "Public/IPostRoundAction.h"
#include "Public/MustBuyCard.h"

Match::Match(const std::string& matchName)
    : Entity{matchName}, Flow{ETurnFlow::Clockwise}
{
    JoinedPlayers.reserve(MAX_NUMBER_OF_PLAYERS);
}

void Match::Begin()
{
    Entity::Begin();
    StartNewMatch();
}

void Match::Tick()
{
    Entity::Tick();

    if(MatchReady && !IsMatchEnded())
    {
        PlayTurn();
    }
}

void Match::StartNewMatch()
{
    Core::LogMessage("Starting Match: " + GetName());
    PlayersCount = ReadNumberOfPlayers();
    JoinPlayers(PlayersCount);
    CreateDeck();
    SortCardsToPlayers();
    SetupTurn();

    MatchReady = true;
}

int Match::ReadNumberOfPlayers()
{
    const int numPlayers = Core::GetInput<int>("How many players will join this match? (Must be between 2 and " + std::to_string(MAX_NUMBER_OF_PLAYERS) + "): ");
    while (numPlayers < 2 || numPlayers > MAX_NUMBER_OF_PLAYERS)
    {
        Core::LogMessage(std::to_string(numPlayers) + " players are not allowed. Select a number between 2 and " + std::to_string(MAX_NUMBER_OF_PLAYERS));
        return ReadNumberOfPlayers();
    }

    return numPlayers;
}

void Match::JoinPlayers(const int number)
{
    for (int i=0; i < number; i++)
    {
        JoinedPlayers.emplace_back(CreatePlayer(i));
    }
}

EntityPtr<Player> Match::CreatePlayer(const int index)
{
    const auto playerName = Core::GetInput<std::string>("Player " + std::to_string(index) + ": What's your name? ");
    for (const EntityPtr<Player>& currentPlayer : JoinedPlayers)
    {
        if(currentPlayer->GetName() == playerName)
        {
            Core::LogMessage("You can't assign your name as " + playerName + " because another player already has this name");
            return CreatePlayer(index);
        }
    }

    return Engine::CreateEntity<Player>(playerName, index);
}

void Match::CreateDeck()
{
    Deck = Engine::CreateEntity<DeckController>("Deck Controller");
}

void Match::SortCardsToPlayers()
{
    Deck->ShuffleDeckCards();

    for (const EntityPtr<Player>& player : JoinedPlayers)
    {
        for (int i=0; i < INITIAL_CARDS_PER_PLAYER; i++)
        {
            player->BuyDeckCard(Deck.GetWeakPtr());
        }
    }
}

void Match::SetupTurn()
{
    CurrentTurn = 0;
    CurrentPlayerIndex = Core::RandomRange(0, PlayersCount - 1);
    Flow = Core::RandomRange(0, 1) == 0 ? ETurnFlow::Clockwise : ETurnFlow::AntiClockwise;
}

void Match::PostRoundAction(const EntityPtr<Card>& tossedCard)
{
    if(LastCard == tossedCard)
    {
        return;
    }

    auto* postRound = tossedCard.ImplementsInterface<IPostRoundAction>();
    if(postRound != nullptr)
    {
        postRound->Execute(this);
    }
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

EntityPtr<Round> Match::MakeRound()
{
    EntityPtr<Round> newRound;

    const EntityPtr<Card>& tossedCard = Deck->GetLastTossedCard();
    if(tossedCard.IsValid() && tossedCard != LastCard)
    {
        const auto customRoundCard = tossedCard.ImplementsInterface<ICustomRoundCard>();
        if (customRoundCard != nullptr)
        {
            newRound = customRoundCard->GenerateCustomRound(CurrentTurn);
        }
    }

    if(!newRound.IsValid())
    {
        newRound = Engine::CreateEntity<Round>(CurrentTurn);
    }

    return newRound;
}

void Match::PlayTurn()
{
    const EntityPtr<Player>& currentPlayerTurn = JoinedPlayers[CurrentPlayerIndex];

    EntityPtr<Round> newRound = MakeRound();
    LastCard = Deck->GetLastTossedCard();

    newRound->RunRound(currentPlayerTurn, Deck, Flow);

    if(currentPlayerTurn->GetCards().empty())
    {
        Core::WaitAnyKey(GetConsoleColorCode(EColor::Green) +
            "CONGRATULATIONS " + currentPlayerTurn->GetName() + "!!! You won the game!" +
            GetConsoleColorCode(EColor::None));
        FinishMatch();
        return;
    }

    PostRoundAction(Deck->GetLastTossedCard());

    IncreaseTurn();

    Core::WaitAnyKey("Press any key to go to next turn");
}

void Match::ReverseFlow()
{
    Flow = Flow == ETurnFlow::Clockwise ? ETurnFlow::AntiClockwise : ETurnFlow::Clockwise;
    Core::WaitAnyKey("THE FLOW OF THE GAME HAS CHANGED! New flow: " + GetFlowName(Flow));
}

void Match::Restart()
{
    for (const EntityPtr<Player>& player : JoinedPlayers)
    {
        for (EntityPtr<Card>& playerCard : player->GetCards())
        {
            Deck->AddCardToDeck(playerCard);
        }
        player->GetCards().clear();
    }

    Deck->ShuffleTossedCardsBackToDeck();
    MatchFinished = false;

    Core::LogMessage("Restarting Match: " + GetName());
    SortCardsToPlayers();
    SetupTurn();

    MatchReady = true; 
}

bool Match::IsMatchEnded() const
{
    return MatchFinished;
}

int Match::GetPlayersAmount() const
{
    return static_cast<int>(JoinedPlayers.size());
}

const EntityPtr<Player>& Match::GetCurrentPlayer() const
{
    return JoinedPlayers.at(CurrentPlayerIndex);
}

const std::vector<EntityPtr<Player>>& Match::GetPlayers() const
{
    return JoinedPlayers;
}

void Match::FinishMatch()
{
    MatchReady = false;
    MatchFinished = true;
}