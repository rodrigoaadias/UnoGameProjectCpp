#pragma once
#include <vector>
#include "ETurnFlow.h"
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Player;

class Match : public Entity
{
    int CurrentTurn;
    ETurnFlow Flow;
    std::vector<EntityPtr<Player>> JoinedPlayers;

    EntityPtr<Player> CreatePlayer(int index);

public:
    Match(const std::string& matchName);

    void StartNewMatch();
    void JoinPlayers(int number);
    void CreateDeck();
    void SortCardsToPlayers();
    void SortFirstPlayerTurn();
    void PlayTurn();
    void ExecuteCardAction();      
    void ExecuteCardTossAction();  
    void SkipTurn();
    void ReverseFlow();
    bool IsMatchEnded();
    void FinishMatch();
};
