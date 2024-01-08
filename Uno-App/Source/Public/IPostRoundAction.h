#pragma once
#include "IMatchContext.h"

class IPostRoundAction
{
public:
    NO_COPY_MOVE(IPostRoundAction)
    VIRTUAL_DESTRUCTOR(IPostRoundAction)

    virtual void Execute(IMatchContext* currentMatch) = 0;
};
