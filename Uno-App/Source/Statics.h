#pragma once
#include "Public/EColor.h"

static constexpr int COLUMN_HEIGHT = 7;
static constexpr char DEFAULT_COLOR[] = "\033[0m";
static constexpr int LINE_WIDTH = 11;
static constexpr int COLOR_DISPLAY_SIZE = 7;
static constexpr int CARDS_PER_LINE = 7;
static constexpr int INITIAL_CARDS_PER_PLAYER = 7;
static constexpr int MAX_NUMBER_OF_PLAYERS = 10;

static std::string GetConsoleColorCode(const EColor color)
{
    switch (color)
    {
    case EColor::Blue:
        return "\033[34m";
    case EColor::Yellow:
        return "\033[33m";
    case EColor::Red:
        return "\033[31m";
    case EColor::Green:
        return "\033[32m";
    case EColor::None:
        return DEFAULT_COLOR;
    }

    return DEFAULT_COLOR;
}