#include "../Public/Entity.h"
#include <iostream>
#include <string>

Entity::Entity(const std::string& entityName)
{
    Name = entityName;
}

void Entity::Begin()
{ }

void Entity::Tick()
{ }

Entity::~Entity()
{
    std::cout << "Destructing " << Name << std::endl;
}

const std::string& Entity::GetName()
{
    return Name;
}

