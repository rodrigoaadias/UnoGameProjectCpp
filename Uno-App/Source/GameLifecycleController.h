#pragma once
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Player;

class GameLifecycleController : public Entity
{
public:
    GameLifecycleController(const std::string& name);
    void Begin() override;
    void Tick() override;

    EntityPtr<Player> PlayerOne;
};
