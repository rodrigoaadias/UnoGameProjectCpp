#include "Core.h"
#include <random>
#include <ranges>
#include <sstream>

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

void Core::LogMessage(const std::string_view message)
{
    std::cout << message << "\n";
}

void Core::LogError(const std::string_view errorMessage)
{
    std::stringstream stream;
    stream << RED_COLOR << errorMessage << DEFAULT_COLOR;
    LogMessage(stream.view());
}

int Core::RandomRange(const int min, const int maxInclusive)
{
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution distribution = std::uniform_int_distribution{min, maxInclusive};

    return distribution(mt);
}

void Core::ClearConsole()
{
    system("cls");
}