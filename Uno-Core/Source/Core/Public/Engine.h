#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Core/EntityPtr.h"

class Engine
{
public:
    inline static std::vector<std::weak_ptr<Core::Entity>> Entities {};

    template <typename TElement>
    static std::shared_ptr<TElement> CreateEntity(const std::string& entityName);

    static void Reserve(int size);
    static void InitEntity(const std::weak_ptr<Core::Entity>& newEntity);
    static void ClearEntities();
    static void RemoveEntity(std::shared_ptr<Core::Entity>& entityToRemove);
    static void Tick();
};

template <typename  TElement> std::shared_ptr<TElement> Engine::CreateEntity(const std::string& entityName)
{
    std::shared_ptr<Core::Entity> newEntity = std::make_shared<TElement>(entityName);
    std::weak_ptr<Core::Entity> weakEntityPtr { newEntity };

    InitEntity(weakEntityPtr);
    std::shared_ptr<TElement> returnValue = std::dynamic_pointer_cast<TElement>(newEntity);
    return returnValue;
}
