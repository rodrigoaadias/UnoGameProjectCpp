#pragma once
#include <cstdint>
#include <string>

enum class ETurnFlow : uint8_t
{
    Clockwise,
    AntiClockwise
};

inline std::string GetFlowName(const ETurnFlow flow)
{
    switch (flow)
    {
    case ETurnFlow::Clockwise:
        return  "Clockwise";
    case ETurnFlow::AntiClockwise:
        return "Anti-clockwise";
    }

    return "Invalid flow";
}