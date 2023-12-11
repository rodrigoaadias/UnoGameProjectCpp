#pragma once
#include <string>

namespace Core
{
    class Entity
    {
        std::string Name {};

    public:
        Entity(const std::string& EntityName);
        const std::string& GetName();

        virtual void Begin();
        virtual void Tick();
        virtual void Destroy();

        ~Entity();
    };
}
