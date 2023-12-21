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
    int CurrentTurn;
    int CurrentPlayerIndex;
    int PlayersCount;
    ETurnFlow Flow;
    bool bMatchReady{false};
    bool bMatchFinished{false};
    
    std::vector<EntityPtr<Player>> JoinedPlayers;
    EntityPtr<DeckController> Deck;

    EntityPtr<Player> CreatePlayer(const int& index);
    void PostRoundAction(const EntityPtr<Card>& tossedCard);
    void IncreaseTurn();
    EntityPtr<Round> MakeRound();
    EntityPtr<Card> LastCard; 

public:
    Match(const std::string& matchName);

    void Begin() override;
    void Tick() override;

    void StartNewMatch();
    int GetNumberOfPlayers();
    void JoinPlayers(const int& number);
    void CreateDeck();
    void SortCardsToPlayers();
    void SetupTurnFlow();
    void PlayTurn();
    void ReverseFlow();
    bool IsMatchEnded();
    void FinishMatch();
};
