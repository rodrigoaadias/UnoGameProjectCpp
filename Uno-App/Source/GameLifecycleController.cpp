#include "GameLifecycleController.h"
#include <iostream>

#include "Player.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"

GameLifecycleController::GameLifecycleController(const std::string& name)
    : Entity{name}
{}

void GameLifecycleController::Begin()
{
    Entity::Begin();

    PlayerOne = Engine::CreateEntity<Player>("Player One");
}

void GameLifecycleController::Tick()
{
    Entity::Tick();

    if (Counter == 3)
    {
        Destroy(std::static_pointer_cast<Entity>(PlayerOne));
    }

    if(Counter < 5)
    {
        Counter++;
        return;
    }
    
    std::cout << "Press any key to quit the game" << std::endl;
    std::cin.get();

    Core::CloseApp();
}
