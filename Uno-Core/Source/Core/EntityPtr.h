#pragma once
#include <assert.h>
#include <iostream>
#include <memory>
#include <ostream>

template <class TElement>
class EntityPtr
{
public:
    std::shared_ptr<TElement>* Instance {nullptr};
    std::shared_ptr<int> RefCount {};

    EntityPtr(std::shared_ptr<TElement>* inInstance)
        : Instance(inInstance), RefCount{std::make_shared<int>()}
    { }

    EntityPtr(std::shared_ptr<TElement>* inInstance, const std::shared_ptr<int>& inRefCount)
        : Instance(inInstance), RefCount{inRefCount}
    { }

    EntityPtr() = default;

    template <typename ...TArgs>
    static EntityPtr MakeEntityPtr(TArgs ...args)
    {
        return EntityPtr(new std::shared_ptr<TElement>( new TElement(args...) ));
    }

    std::shared_ptr<TElement> operator -> ()
    {
        assert(IsValid());
        return *Instance;
    }
    
    std::shared_ptr<TElement> operator -> () const
    {
        assert(IsValid());
        return *Instance;
    }

    template <typename TOther>
    explicit operator EntityPtr<TOther>()
    {
        std::shared_ptr<TOther> castedInstance = std::dynamic_pointer_cast<TOther>(*Instance);
        if(castedInstance)
        {
            EntityPtr<TOther> other = { reinterpret_cast<std::shared_ptr<TOther>*>(Instance), RefCount};
            return other;
        }

        return EntityPtr<TOther>{};
    }

    bool IsValid() const
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

