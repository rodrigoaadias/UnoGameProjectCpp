#include "Public/Card.h"

Card::Card(const std::string& name, const EColor color)
    : Entity{getColorName(color) + " " + name}, Color{color}
{}