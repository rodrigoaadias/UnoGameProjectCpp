#pragma once
#include "Player.h"
#include "Core/Core.h"
#include "Core/EntityPtr.h"

class IMatchContext
{
public:    
    NO_COPY_MOVE(IMatchContext)
    VIRTUAL_DESTRUCTOR(IMatchContext)

    virtual void ReverseFlow() = 0;
    [[nodiscard]] virtual int GetPlayersAmount() const = 0;
    [[nodiscard]] virtual const EntityPtr<Player>& GetCurrentPlayer() const = 0;
    [[nodiscard]] virtual const std::vector<EntityPtr<Player>>& GetPlayers() const = 0;
};
