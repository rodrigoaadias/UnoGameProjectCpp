#pragma once
#include <memory>
#include "Core/Public/Entity.h"

class Player;

class GameLifecycleController : public Core::Entity
{
public:
    GameLifecycleController(const std::string& name);
    void Begin() override;
    void Tick() override;

    int Counter = 0;
    std::shared_ptr<Player> PlayerOne;
};
