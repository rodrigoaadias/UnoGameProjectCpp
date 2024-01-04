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
    int CurrentTurn{0};
    int CurrentPlayerIndex{0};
    int PlayersCount{0};
    ETurnFlow Flow;
    bool MatchReady{false};
    bool MatchFinished{false};
    
    std::vector<EntityPtr<Player>> JoinedPlayers;
    EntityPtr<DeckController> Deck;

    EntityPtr<Player> CreatePlayer(int index);
    void PostRoundAction(const EntityPtr<Card>& tossedCard);
    void IncreaseTurn();
    EntityPtr<Round> MakeRound();
    EntityPtr<Card> LastCard;

    void JoinPlayers(int number);
    void CreateDeck();
    void SortCardsToPlayers();
    void SetupTurn();
    void PlayTurn();
    void FinishMatch();
    int ReadNumberOfPlayers();

public:
    Match(const std::string& matchName);

    void Begin() override;
    void Tick() override;

    void StartNewMatch();

    void ReverseFlow();
    void Restart();

    [[nodiscard]] bool IsMatchEnded() const;
    [[nodiscard]] int GetPlayersAmount() const;
    [[nodiscard]] const EntityPtr<Player>& GetCurrentPlayer() const;
    [[nodiscard]] const std::vector<EntityPtr<Player>>& GetPlayers() const;
};
