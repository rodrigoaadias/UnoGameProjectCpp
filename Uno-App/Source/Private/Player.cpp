#include "Public/Player.h"

Player::Player(const std::string& name, const int& index)
    :Entity(name), Index{index}
{}

const std::string Player::GetDisplayName()
{
    return "Player " + std::to_string(Index)  + ": " + GetName();
}