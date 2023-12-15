#pragma once
#include <assert.h>
#include <iostream>
#include <memory>
#include <ostream>
#include "Public/Entity.h"

template <class TElement>
class EntityPtr
{
public:
    std::shared_ptr<Entity>* Instance {nullptr};
    std::shared_ptr<int> RefCount {};

    EntityPtr(std::shared_ptr<Entity>* inInstance)
        : Instance(inInstance), RefCount{std::make_shared<int>()}
    { }

    EntityPtr(std::shared_ptr<Entity>* inInstance, const std::shared_ptr<int>& inRefCount)
        : Instance(inInstance), RefCount{inRefCount}
    { }

    EntityPtr() = default;

    template <typename ...TArgs>
    static EntityPtr MakeEntityPtr(TArgs ...args)
    {
        return EntityPtr(new std::shared_ptr<Entity>( new TElement(args...) ));
    }

    std::shared_ptr<TElement> operator -> ()
    {
        assert(this.IsValid());
        return *Instance;
    }

    template <typename TOther>
    explicit operator EntityPtr<TOther>()
    {
        std::shared_ptr<TOther> castedInstance = std::dynamic_pointer_cast<TOther>(*Instance);
        if(castedInstance)
        {
            EntityPtr<TOther> other = {Instance, RefCount};
            return other;
        }

        return EntityPtr<TOther>{};
    }

    bool IsValid()
    {
        return Instance && *Instance != nullptr;
    }

    std::weak_ptr<TElement> get()
    {        
        assert(IsValid());
        return std::weak_ptr<TElement>{ *Instance }; 
    }

    void reset()
    {
        Instance->reset();
    }

    virtual ~EntityPtr()
    {
        if(RefCount && RefCount.use_count() == 1)
        {
            assert(Instance);
            Instance->reset();
        }
    }
};

