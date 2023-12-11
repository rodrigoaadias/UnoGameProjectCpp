#pragma once
#include <vector>
#include "Entity.h"

class Engine
{
public:
    inline static std::vector<Core::Entity*> Entities {};
    
public:
    static void Reserve(int size);
    static void InitEntity(Core::Entity* NewEntity);
    static void ClearEntities();
    static void RemoveEntity(Core::Entity* EntityToRemove);
    static void Tick();
};
