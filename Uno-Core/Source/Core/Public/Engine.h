#pragma once
#include <vector>
#include "Entity.h"

class Engine
{
public:
    inline static std::vector<Core::Entity*> Entities {};

    static void Reserve(int size);
    static void InitEntity(Core::Entity* newEntity);
    static void ClearEntities();
    static void RemoveEntity(const Core::Entity* entityToRemove);
    static void Tick();
};
