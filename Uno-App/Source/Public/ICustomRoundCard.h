#pragma once
#include "Round.h"
#include "Core/EntityPtr.h"

class ICustomRoundCard
{
    ICustomRoundCard() = default;
    
public:
    ICustomRoundCard(ICustomRoundCard& other) = delete;
    ICustomRoundCard(ICustomRoundCard&& other) = delete;

    ICustomRoundCard& operator = (const ICustomRoundCard& other) = delete;
    ICustomRoundCard& operator = (const ICustomRoundCard&& other) = delete;    

    virtual EntityPtr<Round> GenerateCustomRound(int roundIndex) = 0;    
    virtual ~ICustomRoundCard() = default;
};
