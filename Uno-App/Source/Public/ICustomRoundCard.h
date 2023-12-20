#pragma once
#include "Round.h"
#include "Core/EntityPtr.h"

class ICustomRoundCard
{
public:
    virtual EntityPtr<Round> GetCustomRound(int roundIndex) = 0;    
    virtual ~ICustomRoundCard() = default;
};
