#include "Player.h"
#include <iostream>

Player::Player(const std::string& name)
    : Entity(name)
{
    std::cout << "Player Created: " << name << std::endl;
}
