#pragma once
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Match;

class GameLifecycleController : public Entity
{
    EntityPtr<Match> CurrentMatch;
    void ShowRestartOptions();
public:
    
    GameLifecycleController(const std::string& name);
    void CreateMatch();
    void Begin() override;
    void Tick() override;
};
