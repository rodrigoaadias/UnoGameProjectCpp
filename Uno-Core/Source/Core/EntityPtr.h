#pragma once
#include <assert.h>
#include <memory>
#include <ostream>

template <class TElement>
class EntityPtr
{
public:
    std::shared_ptr<TElement>* Instance {nullptr};
    std::shared_ptr<int> RefCount {};

    explicit EntityPtr(std::shared_ptr<TElement>* inInstance)
        : Instance(std::move(inInstance)), RefCount{std::make_shared<int>()}
    { }

    EntityPtr(std::shared_ptr<TElement>* inInstance, const std::shared_ptr<int>& inRefCount)
        : Instance(std::move(inInstance)), RefCount{inRefCount}
    { }

    EntityPtr() = default;

    EntityPtr(const EntityPtr& other)
    {
        Instance = other.Instance;
        RefCount = other.RefCount;
    }

    EntityPtr(EntityPtr&& other) noexcept
    {
        Instance = other.Instance;
        RefCount = other.RefCount;
        other.Instance = nullptr;
        other.RefCount.reset();
    }

    EntityPtr& operator = (const EntityPtr& other)
    {
        if(this == &other)
        {
            return *this;
        }

        Instance = other.Instance;
        RefCount = other.RefCount;
        return *this;
    }

    EntityPtr& operator = (EntityPtr&& other) noexcept
    {
        Instance = other.Instance;
        RefCount = other.RefCount;
        other.Instance = nullptr;
        other.RefCount.reset();
        return *this;
    }

    // template <typename ...TArgs>
    // static EntityPtr MakeEntityPtr(TArgs&& ...args)
    // {
    //     return EntityPtr(new std::shared_ptr<TElement>( new TElement(args...) ));
    // }

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

    bool operator==(const EntityPtr& other) const
    {
        return Instance == other.Instance && IsValid() && other.IsValid();
    }

    template <typename TOther>
    explicit operator EntityPtr<TOther>() const
    {
        std::shared_ptr<TOther> castedInstance = std::dynamic_pointer_cast<TOther>(*Instance);
        if(castedInstance)
        {
            EntityPtr<TOther> other = { reinterpret_cast<std::shared_ptr<TOther>*>(Instance), RefCount};
            return other;
        }

        return EntityPtr<TOther>{};
    }

    template<class TInterface>
    TInterface* ImplementsInterface() const
    {
        std::shared_ptr<TInterface> interface = std::dynamic_pointer_cast<TInterface>(*Instance);
        if(interface != nullptr)
        {
            return interface.get();
        }

        return nullptr;
    }

    bool IsValid() const
    {
        return Instance && *Instance != nullptr;
    }

    std::weak_ptr<TElement> GetWeakPtr()
    {        
        assert(IsValid());
        
        return std::weak_ptr<TElement>{ *Instance }; 
    }

    TElement& GetRef()
    {
        assert(IsValid());
        return **Instance;
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

