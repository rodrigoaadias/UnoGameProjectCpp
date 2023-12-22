#pragma once
#include <memory>

static constexpr int COLUMN_HEIGHT = 7;
static constexpr char DEFAULT_COLOR[] = "\033[0m";
static constexpr int LINE_WIDTH = 11;

template <typename TInterface, typename TObjectType>
TInterface* ImplementsInterface(std::shared_ptr<TObjectType> sharedPtr)
{
    std::shared_ptr<TInterface> interface = std::dynamic_pointer_cast<TInterface>(sharedPtr);
    if(interface != nullptr)
    {
        return interface.get();
    }

    return nullptr;
}