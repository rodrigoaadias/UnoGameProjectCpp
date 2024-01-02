#pragma once
#include <string>

class Entity
{
    std::string Name {};

public:
    Entity(const Entity& other);
    Entity& operator = (const Entity& other);

    Entity(Entity&& other) = delete;
    Entity& operator = (const Entity&& other) = delete;

    explicit Entity(const std::string& entityName);
    [[nodiscard]] const std::string& GetName() const;

    virtual void Begin();
    virtual void Tick();

    virtual ~Entity();
};

