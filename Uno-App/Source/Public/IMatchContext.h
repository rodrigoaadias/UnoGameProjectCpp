#pragma once
#include "Player.h"
#include "Core/EntityPtr.h"

class IMatchContext
{
public:
    IMatchContext() = default;
    IMatchContext(IMatchContext& other) = delete;
    IMatchContext(IMatchContext&& other) = delete;

    IMatchContext& operator = (const IMatchContext& other) = delete;
    IMatchContext& operator = (const IMatchContext&& other) = delete;    

    virtual void ReverseFlow() = 0;
    [[nodiscard]] virtual int GetPlayersAmount() const = 0;
    [[nodiscard]] virtual const EntityPtr<Player>& GetCurrentPlayer() const = 0;
    [[nodiscard]] virtual const std::vector<EntityPtr<Player>>& GetPlayers() const = 0;

    virtual ~IMatchContext() = default;
};
