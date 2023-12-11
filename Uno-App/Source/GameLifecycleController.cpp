#include "GameLifecycleController.h"
#include <iostream>
#include "Core/Core.h"

GameLifecycleController::GameLifecycleController()
    : Entity("Lifecycle Controller")
{    
}

void GameLifecycleController::Tick()
{
    Entity::Tick();
    std::cout << "Press any key to quit the game" << std::endl;
    std::cin.get();

    Core::CloseApp();
}
