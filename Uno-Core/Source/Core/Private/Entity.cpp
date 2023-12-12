#include "../Public/Entity.h"

#include <iostream>

#include "Core/Public/Engine.h"
#include <string>

namespace Core
{
    Entity::Entity(const std::string& entityName)
    {
        Name = entityName;
        Engine::InitEntity(this);
    }

    void Entity::Begin()
    { }

    void Entity::Tick()
    { }

    void Entity::Destroy()
    {
        Engine::RemoveEntity(this);
        delete this;
    }

    Entity::~Entity()
    {
        std::cout << "Destructing " << Name << std::endl;
    }

    const std::string& Entity::GetName()
    {
        return Name;
    }
}
