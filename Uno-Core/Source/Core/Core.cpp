#include "Core.h"

#include <iostream>

#include "Public/Engine.h"

namespace Core {

	void RunEngine()
	{
		Engine::Reserve(100);
		WantsToClose = false;

		while (!WantsToClose)
		{
			Engine::Tick();
		}

		Engine::ClearEntities();
		std::cin.get();
	}

	void CloseApp()
	{
		WantsToClose = true;
	}	
}
