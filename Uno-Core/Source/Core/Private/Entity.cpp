#include "../Public/Entity.h"
#include <iostream>
#include "Core/Public/Engine.h"
#include <string>

namespace Core
{
    Entity::Entity(const std::string& entityName)
    {
        Name = entityName;
    }

    void Entity::Begin()
    { }

    void Entity::Tick()
    { }

    void Entity::Destroy(std::shared_ptr<Entity>& entity)
    {
        Engine::RemoveEntity(entity);
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
