#include "Public/Card.h"
#include "Statics.h"
#include "Core/Core.h"

Card::Card(const std::string& name, const EColor color)
    : Entity{GetColorName(color) + " " + name}, Color{color}
{}

EColor Card::GetColor() const
{
    return Color;
}

bool Card::CanTossCardOnMe(const EntityPtr<Card>& other) const
{
    return !other.IsValid() || Color == other->GetColor() || other->GetColor() == EColor::None || Color == EColor::None;
}