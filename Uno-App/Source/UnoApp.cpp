#include "Public/GameLifecycleController.h"
#include "Core/Core.h"
#include "Core/Public/Engine.h"

static uint32_t sAllocCount = 0;

void* operator new (size_t size)
{
    sAllocCount++;
    std::cout << "Allocating " << size << " bytes\n";
    return malloc(size);
}

int main()
{
    //EntityPtr<GameLifecycleController> gameLifecycleController = Engine::CreateEntity<GameLifecycleController>("Lifecycle Controller");
    //Core::RunEngine();

    constexpr int anyNumberFromSomewhere = 15;
    Core::LogMessage("Testing allocations: " + std::to_string(anyNumberFromSomewhere));
    std::cout << "Allocations: " << sAllocCount << "\n";
}