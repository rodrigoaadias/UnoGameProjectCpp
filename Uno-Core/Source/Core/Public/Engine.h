﻿#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Core/EntityPtr.h"

class Engine
{
public:
    inline static std::vector<std::weak_ptr<Entity>> Entities {};

    template <typename TElement, typename ...TArgs> 
    static EntityPtr<TElement> CreateEntity(TArgs ...args);

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

template <typename TElement, typename ...TArgs> EntityPtr<TElement> Engine::CreateEntity(TArgs ...args)
{
    EntityPtr<TElement> newEntity = EntityPtr<TElement>::MakeEntityPtr(args...);
    EntityPtr<Entity> entityCast = static_cast<EntityPtr<Entity>>(newEntity);
    InitEntity(entityCast.get());
    return newEntity;
}