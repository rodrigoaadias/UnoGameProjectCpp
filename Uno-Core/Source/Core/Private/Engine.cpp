#include "../Public/Engine.h"

void Engine::Reserve(const int size)
{
    Entities.reserve(size);
}

void Engine::InitEntity(const std::weak_ptr<Entity>& newEntity)
{
    const std::shared_ptr<Entity> sharedNewEntity = newEntity.lock(); 
    Entities.emplace_back(newEntity);
    sharedNewEntity->Begin();
}

void Engine::ClearEntities()
{
    Entities.clear();
}

void Engine::Destroy(EntityPtr<Entity>& entityToRemove)
{
    entityToRemove.reset();
}

void Engine::Tick()
{
    for (int i = 0; i < static_cast<int>(Entities.size()) ; i++)
    {
        if(Entities[i].expired())
        {
            Entities.erase(Entities.begin() + i);
            i--;
            break;
        }

        const std::shared_ptr<Entity> sharedEntity = Entities[i].lock();
        sharedEntity->Tick();
    }
}