#include "GameLifecycleController.h"
#include <iostream>
#include "Core/Core.h"
#include "Core/Public/Engine.h"

GameLifecycleController::GameLifecycleController(const std::string& name)
    : Entity(name)
{}

void GameLifecycleController::Begin()
{
    Entity::Begin();
}

void GameLifecycleController::Tick()
{
    Entity::Tick();
    std::cout << "Press any key to quit the game" << std::endl;
    std::cin.get();

    Core::CloseApp();
}
