#pragma once
#include "Round.h"
#include "Core/Core.h"
#include "Core/EntityPtr.h"

class ICustomRoundCard
{    
public:
    NO_COPY_MOVE(ICustomRoundCard)
    VIRTUAL_DESTRUCTOR(ICustomRoundCard)

    virtual EntityPtr<Round> GenerateCustomRound(int roundIndex) = 0;        
};
