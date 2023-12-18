#pragma once
#include <memory>
#include <vector>
#include "Card.h"
#include "Core/Public/Entity.h"

class Player : public Entity
{
    int Index;
    std::vector<std::weak_ptr<Card>> CardsOnHand;
    
public:
    Player(const std::string& name, const int& index);
    std::string GetDisplayName();

    void AddCardToHand(std::weak_ptr<Card> card);
    std::string ToString();
};
