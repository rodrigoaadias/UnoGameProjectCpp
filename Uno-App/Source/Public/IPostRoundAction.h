#pragma once
#include "IMatchContext.h"

class IPostRoundAction
{
public:
    IPostRoundAction() = default;
    IPostRoundAction(const IPostRoundAction& other) = delete;
    IPostRoundAction(const IPostRoundAction&& other) = delete;

    IPostRoundAction& operator = (const IPostRoundAction& other) = delete;
    IPostRoundAction& operator = (const IPostRoundAction&& other) = delete;

    virtual void Execute(IMatchContext* currentMatch) = 0;
    virtual ~IPostRoundAction() = default;
};
