#pragma once
#include "Core/Public/Entity.h"

class GameLifecycleController : Core::Entity
{
public:
    GameLifecycleController();
    void Tick() override;
};
