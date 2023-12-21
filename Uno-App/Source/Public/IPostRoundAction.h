#pragma once
#include "Match.h"

class IPostRoundAction
{
public:
    virtual void Execute(Match* currentMatch) = 0;
    virtual ~IPostRoundAction() = default;
};
