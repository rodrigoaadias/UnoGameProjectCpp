#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Core/EntityPtr.h"

class Engine
{
public:
    inline static std::vector<std::weak_ptr<Entity>> Entities {};

    template <typename TElement>
    static EntityPtr<TElement> CreateEntity(const std::string& entityName);

    static void Reserve(int size);
    static void InitEntity(const std::weak_ptr<Entity>& newEntity);
    static void ClearEntities();
    static void Destroy(EntityPtr<Entity>& entityToRemove);
    static void Tick();  

    template <class TElement> static void Destroy(EntityPtr<TElement>& entity)
    {
        entity.reset();     
    }
};

template <typename TElement> EntityPtr<TElement> Engine::CreateEntity(const std::string& entityName)
{
    EntityPtr<TElement> newEntity = EntityPtr<TElement>::MakeEntityPtr(entityName);
    EntityPtr<Entity> entityCast = static_cast<EntityPtr<Entity>>(newEntity);
    InitEntity(entityCast.get());
    return newEntity;
}