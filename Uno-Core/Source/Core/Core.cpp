#include "Core.h"
#include "Public/Engine.h"

namespace Core {

	void RunEngine()
	{
		Engine::Reserve(100);
		WANTS_TO_CLOSE = false;	    

		while (!WANTS_TO_CLOSE)
		{
			Engine::Tick();
		}

		Engine::ClearEntities();
	}

	void CloseApp()
	{
		WANTS_TO_CLOSE = true;
	}
}
