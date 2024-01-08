#pragma once
#include "EColor.h"
#include "Core/EntityPtr.h"
#include "Core/Public/Entity.h"

class Card : public Entity
{
    EColor Color;

public:
    Card(const std::string& name, EColor color);
    [[nodiscard]] EColor GetColor() const;

    [[nodiscard]] virtual std::string GetCardTypeName() const = 0;
    [[nodiscard]] virtual bool CanTossCardOnMe(const EntityPtr<Card>& other) const;
};
