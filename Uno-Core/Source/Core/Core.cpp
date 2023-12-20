#include "Core.h"
#include "Public/Engine.h"


void Core::RunEngine()
{
	Engine::Reserve(100);
	WantsToClose = false;

	while (!WantsToClose)
	{
		Engine::Tick();
	}

	Engine::ClearEntities();
}

void Core::CloseApp()
{
	WantsToClose = true;
}

void Core::WaitAnyKey(const std::string& message)
{
    LogMessage(message);
    std::cin.get();
}

void Core::LogMessage(const std::string& message)
{
    std::cout << message << std::endl;
}

void Core::LogError(const std::string& errorMessage)
{
    LogMessage("\033[31m" + errorMessage + "\033[0m");
}