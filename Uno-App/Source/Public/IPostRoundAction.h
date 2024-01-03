#pragma once
#include "Match.h"

class IPostRoundAction
{
    IPostRoundAction() = default;
public:
    IPostRoundAction(const IPostRoundAction& other) = delete;
    IPostRoundAction(const IPostRoundAction&& other) = delete;

    IPostRoundAction& operator = (const IPostRoundAction& other) = delete;
    IPostRoundAction& operator = (const IPostRoundAction&& other) = delete;

    virtual void Execute(Match* currentMatch) = 0;
    virtual ~IPostRoundAction() = default;
};
