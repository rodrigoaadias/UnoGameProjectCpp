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
