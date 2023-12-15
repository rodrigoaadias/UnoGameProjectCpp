#pragma once
#include "EColor.h"
#include "Core/Public/Entity.h"

class Card : public Entity
{
    EColor Color;
public:
    explicit Card(const std::string& name, EColor color);
    EColor GetColor() const { return Color; }
};