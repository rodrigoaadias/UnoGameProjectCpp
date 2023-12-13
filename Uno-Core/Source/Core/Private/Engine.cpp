#include "../Public/Engine.h"

void Engine::Reserve(int size)
{
    Entities.reserve(size);
}

void Engine::InitEntity(Core::Entity* newEntity)
{
    newEntity->Begin();
    Entities.push_back(newEntity);
}

void Engine::ClearEntities()
{
    for (const Core::Entity* Entity : Entities)
    {
        delete Entity;
    }

    Entities.clear();
}

void Engine::RemoveEntity(const Core::Entity* entityToRemove)
{
    for (int i = 0; i < Entities.size() ; i++)
    {
        if(Entities[i] == entityToRemove)
        {
            Entities.erase(Entities.begin() + i);
            break;
        }
    }
}

void Engine::Tick()
{
    for (int i = 0; i < Entities.size() ; i++)
    {
        if(Entities[i] == nullptr)
        {
            Entities.erase(Entities.begin() + i);
            i--;
            break;
        }

        Entities[i]->Tick();
    }
}
