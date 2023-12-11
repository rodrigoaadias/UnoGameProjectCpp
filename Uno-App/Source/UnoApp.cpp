#include "GameLifecycleController.h"
#include "Player.h"
#include "Core/Core.h"
#include "Core/Public/Entity.h"

int main()
{
	Player* player1 = new Player("Player One");
	Player* player2 = new Player("Player Two");
	new GameLifecycleController();
	Core::RunEngine();
}
