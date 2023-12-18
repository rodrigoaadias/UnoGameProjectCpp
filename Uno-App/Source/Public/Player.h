#pragma once
#include "Core/Public/Entity.h"

class Player : public Entity
{
private:
    int Index;
    
public:
    Player(const std::string& name, const int& index);
    const std::string GetDisplayName();
};
