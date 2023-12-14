#include "GameLifecycleController.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"

int main()
{
    std::shared_ptr<GameLifecycleController> gameLifecycleController = Engine::CreateEntity<GameLifecycleController>("Lifecycle Controller");
    Core::RunEngine();
}