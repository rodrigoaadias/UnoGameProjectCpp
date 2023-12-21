#pragma once
#include <vector>
#include "ETurnFlow.h"
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

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
    bool bMatchReady{false};
    bool bMatchFinished{false};
    
    std::vector<EntityPtr<Player>> JoinedPlayers;
    EntityPtr<DeckController> Deck;

    EntityPtr<Player> CreatePlayer(const int& index);
    void IncreaseTurn();
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
