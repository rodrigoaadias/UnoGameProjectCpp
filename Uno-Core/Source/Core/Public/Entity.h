#pragma once
#include <string>

class Entity
{
    std::string Name {};

public:
    Entity(const std::string& entityName);
    const std::string& GetName();

    virtual void Begin();
    virtual void Tick();

    virtual ~Entity();
};

