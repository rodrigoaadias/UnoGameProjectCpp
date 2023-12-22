#pragma once
#include <vector>
#include "ETurnFlow.h"
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Round;
class Card;
class Player;
class DeckController;

class Match : public Entity
{
    static constexpr int INITIAL_CARDS_PER_PLAYER = 7;
    
    int CurrentTurn;
    int CurrentPlayerIndex;
    int PlayersCount;
    ETurnFlow Flow;
    bool MatchReady{false};
    bool MatchFinished{false};
    
    std::vector<EntityPtr<Player>> JoinedPlayers;
    EntityPtr<DeckController> Deck;

    EntityPtr<Player> CreatePlayer(const int& index);
    void PostRoundAction(const EntityPtr<Card>& tossedCard);
    void IncreaseTurn();
    EntityPtr<Round> MakeRound();
    EntityPtr<Card> LastCard;

    void JoinPlayers(const int& number);
    void CreateDeck();
    void SortCardsToPlayers();
    void SetupTurn();
    void PlayTurn();
    void FinishMatch();

public:
    Match(const std::string& matchName);

    void Begin() override;
    void Tick() override;

    void StartNewMatch();
    int ReadNumberOfPlayers();

    void ReverseFlow();
    bool IsMatchEnded() const;
    void Restart();
    int GetPlayersAmount() const;
    EntityPtr<Player> GetCurrentPlayer() const;
    std::vector<EntityPtr<Player>> GetPlayers() const;
};
