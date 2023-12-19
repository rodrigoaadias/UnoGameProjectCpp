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
    Core::LogMessage("Welcome to the UNO GAME - PLUS PLUS YOUR LIFE\n");
    Core::LogMessage("Would you like to start a new Match?");
    const int choice = Core::GetInput<int>("1 - Yes;  2 - No, quit the game: ");
    if(choice == 1)
    {
        const auto matchName = Core::GetInput<std::string>("Give a name to your match: ");
        CurrentMatch = Engine::CreateEntity<Match>(matchName);
    }
}

void GameLifecycleController::Tick()
{
    Entity::Tick();

    if(CurrentMatch.IsValid())
    {
        if(CurrentMatch->IsMatchEnded())
        {
            Engine::Destroy(CurrentMatch);
        }

        return;
    }

    Core::LogMessage("THANK YOU FOR PLAYING!");
    Core::LogMessage("Press any key to quit the game");
    std::cin.get();

    Core::CloseApp();
}
