#pragma once

#include <memory>
#include <vector>

#include "Component.h"

// TODO: Find all components by type
// TODO: Find entities by component types

template<class TComponent>
TComponent* FindComponent(const std::vector<std::shared_ptr<Component>>& components)
{
    for (int index = 0; index < static_cast<int>(components.size()); index++)
    {
        Component* current = components[index].get();
        if (TComponent* component = dynamic_cast<TComponent*>(current))
        {
            return component;
        }
    }

    return nullptr;
}

template<class TComponent>
void RemoveComponentByType(std::vector<std::shared_ptr<Component>>& components)
{
    for (auto iterator = components.begin(); iterator != components.end();)
    {
        Component* current = (*iterator).get();
        if (TComponent* component = dynamic_cast<TComponent*>(current))
        {
            iterator = components.erase(iterator);
            return;
        }
        ++iterator;
    }
}

template<class TComponent>
void RemoveComponentByPointer(const TComponent* component, std::vector<std::shared_ptr<Component>>& components)
{
    for (auto iterator = components.begin(); iterator != components.end();)
    {
        Component* current = (*iterator).get();
        if (current == component)
        {
            iterator = components.erase(iterator);
            return;
        }
        ++iterator;
    }
}