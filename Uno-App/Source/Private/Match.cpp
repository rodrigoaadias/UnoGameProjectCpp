#include "Public/Match.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"
#include "Public/DeckController.h"
#include "Public/Player.h"
#include "Public/ICustomRoundCard.h"
#include "Public/Round.h"
#include "Public/IPostRoundAction.h"
#include "Public/MustBuyCard.h"

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

    if(MatchReady && !IsMatchEnded())
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
    SetupTurn();

    MatchReady = true;
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
    const auto currentPlayerTurn = JoinedPlayers[CurrentPlayerIndex];
    EntityPtr<Round> newRound;

    // execute pre turn actions
    const auto tossedCard = Deck->GetLastTossedCard();
    if(tossedCard.IsValid() && tossedCard != LastCard)
    {
        const auto customRoundCard = tossedCard.ImplementsInterface<ICustomRoundCard>();
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

    return newRound;
}

void Match::PlayTurn()
{
    const auto currentPlayerTurn = JoinedPlayers[CurrentPlayerIndex];

    EntityPtr<Round> newRound = MakeRound();
    LastCard = Deck->GetLastTossedCard();

    newRound->RunRound(currentPlayerTurn, Deck, Flow);

    if(currentPlayerTurn->GetCards().empty())
    {
        Core::WaitAnyKey("CONGRATULATIONS " + currentPlayerTurn->GetName() + "!!! You won the game!");
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

bool Match::IsMatchEnded() const
{
    return MatchFinished;
}

void Match::Restart()
{
    for (EntityPtr<Player>& player : JoinedPlayers)
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

void Match::FinishMatch()
{
    MatchReady = false;
    MatchFinished = true;
}