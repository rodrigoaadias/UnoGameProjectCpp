#include "../Public/Engine.h"

void Engine::Reserve(const int size)
{
    Entities.reserve(size);
}

void Engine::InitEntity(const std::weak_ptr<Core::Entity>& newEntity)
{
    const std::shared_ptr<Core::Entity> sharedNewEntity = newEntity.lock(); 
    Entities.push_back(newEntity);
    sharedNewEntity->Begin();
}

void Engine::ClearEntities()
{
    for (const std::weak_ptr<Core::Entity>& entity : Entities)
    {
        if(entity.expired())
        {
            continue;
        }

        std::shared_ptr<Core::Entity> sharedEntity = entity.lock();
        RemoveEntity(sharedEntity);
    }

    Entities.clear();
}

void Engine::RemoveEntity(std::shared_ptr<Core::Entity>& entityToRemove)
{
    for (int i = 0; i < static_cast<int>(Entities.size()) ; i++)
    {
        std::shared_ptr<Core::Entity> sharedRef = Entities[i].lock();
        if(sharedRef == entityToRemove)
        {
            Entities.erase(Entities.begin() + i);
            entityToRemove.reset();
            break;
        }
    }
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

        const std::shared_ptr<Core::Entity> sharedEntity = Entities[i].lock();
        sharedEntity->Tick();
    }
}