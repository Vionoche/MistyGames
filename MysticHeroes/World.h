#pragma once

#include <memory>
#include <vector>

#include "Component.h"

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
std::vector<TComponent*> FindComponents(const std::vector<std::shared_ptr<Component>>& components)
{
    std::vector<TComponent*> results;

    for (auto& current : components)
    {
        if (TComponent* component = dynamic_cast<TComponent*>(current.get()))
        {
            results.push_back(component);
        }
    }

    return results;
}

template<class TComponent>
void RemoveComponentByType(std::vector<std::shared_ptr<Component>>& components)
{
    for (auto iterator = components.begin(); iterator != components.end();)
    {
        Component* current = (*iterator).get();
        if (dynamic_cast<TComponent*>(current))
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

template<class TComponent>
Entity * FindEntityByComponent(const std::vector<Entity*>& entities)
{
    for (auto& entity : entities)
    {
        if (FindComponent<TComponent>(entity->Components))
        {
            return entity;
        }
    }

    return nullptr;
}