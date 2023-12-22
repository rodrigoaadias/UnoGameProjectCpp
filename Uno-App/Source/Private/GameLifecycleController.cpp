#include "Public/GameLifecycleController.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"
#include "Public/Match.h"

GameLifecycleController::GameLifecycleController(const std::string& name)
    : Entity(name)
{}

void GameLifecycleController::CreateMatch()
{
    Core::ClearConsole();
    const auto matchName = Core::GetInput<std::string>("Give a name to your match: ");
    CurrentMatch = Engine::CreateEntity<Match>(matchName);
}

void GameLifecycleController::Begin()
{
    Entity::Begin();
    Core::LogMessage("Welcome to the UNO GAME - PLUS PLUS YOUR LIFE\n");
    Core::LogMessage("Would you like to start a new Match?");
    const int choice = Core::GetInput<int>("1 - Yes: ");
    if(choice == 1)
    {
        CreateMatch();
    }
}

void GameLifecycleController::Tick()
{
    Entity::Tick();

    if(CurrentMatch.IsValid())
    {
        if(CurrentMatch->IsMatchEnded())
        {
            ShowRestartOptions();
        }

        return;
    }

    Core::ClearConsole();
    Core::LogMessage("THANK YOU FOR PLAYING!");
    Core::WaitAnyKey("Press any key to quit the game");

    Core::CloseApp();
}

void GameLifecycleController::ShowRestartOptions()
{
    Core::ClearConsole();
    Core::LogMessage(CurrentMatch->GetName() + " finished. What would you like to do?");
    const int choice = Core::GetInput<int>("1 - Replay the same match with the same players\n2 - Play a fresh new match\n[Any] - Quit game\n");
    switch (choice)
    {
    case 1:
        CurrentMatch->Restart();
        break;
    case 2:
        Engine::Destroy(CurrentMatch);
        CreateMatch();
        break;
    default:            
        Engine::Destroy(CurrentMatch);
        break;
    }

}