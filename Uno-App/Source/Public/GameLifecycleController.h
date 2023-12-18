#pragma once
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Match;
class Player;

class GameLifecycleController : public Entity
{
public:
    EntityPtr<Match> CurrentMatch;
    
    GameLifecycleController(const std::string& name);
    void Begin() override;
    void Tick() override;
};
