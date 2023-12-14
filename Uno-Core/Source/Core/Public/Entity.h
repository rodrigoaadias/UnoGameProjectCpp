#pragma once
#include <memory>
#include <string>

namespace Core
{
    class Entity
    {
        std::string Name {};

    public:
        Entity(const std::string& entityName);
        const std::string& GetName();

        virtual void Begin();
        virtual void Tick();

        void Destroy(std::shared_ptr<Entity>& entity);

        virtual ~Entity();
    };
}
