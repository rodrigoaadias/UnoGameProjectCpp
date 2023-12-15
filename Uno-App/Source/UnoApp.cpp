#include "Public/GameLifecycleController.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"

int main()
{
    EntityPtr<GameLifecycleController> gameLifecycleController = Engine::CreateEntity<GameLifecycleController>("Lifecycle Controller");
    Core::RunEngine();
}