#pragma once
#include <cstdint>
#include <string>

enum class EColor : uint8_t
{
    Blue,
    Yellow,
    Red,
    Green,
    None
};

static std::string getColorName(EColor color)
{
    switch (color)
    {
    case EColor::Blue:
        return "Blue";
    case EColor::Yellow:
        return "Yellow";
    case EColor::Red:
        return "Red";
    case EColor::Green:
        return "Green";
    }

    return "Invalid";
}