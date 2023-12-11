#include "Player.h"
#include <iostream>

Player::Player(std::string Name)
    : Entity(Name)
{
    std::cout << "Creating Player: " << Name << std::endl;
}
