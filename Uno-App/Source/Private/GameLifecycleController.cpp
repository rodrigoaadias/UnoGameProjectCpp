#include "Public/GameLifecycleController.h"
#include <iostream>
#include "Core/Core.h"
#include "Core/Public/Engine.h"
#include "Public/DeckController.h"
#include "Public/Match.h"

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
    EntityPtr<Match> match = Engine::CreateEntity<Match>("Test Match");
    match->StartNewMatch();

    Core::LogMessage("Press any key to quit the game");
    std::cin.get();

    Core::CloseApp();
}
