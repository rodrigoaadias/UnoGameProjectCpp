#pragma once
#include <memory>

template <class TElement, class... _Args>
class EntityPtr
{
private:
    std::shared_ptr<TElement> SharedRef;

public:

    static EntityPtr MakeEntityPtr(_Args&&... _args)
    {
        return EntityPtr { std::make_shared<TElement>(_args) };
    }

    bool IsValid()
    {
        return SharedRef != nullptr;
    }
};
