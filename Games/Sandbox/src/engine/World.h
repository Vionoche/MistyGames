#pragma once
#include <vector>

int Example();

class Component
{
    
};

class Health : public Component
{
public:
    int HealthPoints;
};

class Position: public Component
{
public:
    int X;
    int Y;
};

template<class T, class U>
concept Derived = std::is_base_of_v<U, T>;

class Entity
{
public:
    Entity(int id)
    {
        Id = id;
    }

    int Id;
    std::vector<Component> Components;
};

class World
{
public:
    std::vector<Entity*> Entities;

    Entity* CreateEntity()
    {
        _entityCount++;

        Entity* entity = new Entity(_entityCount);
        Entities.push_back(entity);

        return entity;
    }

    void DeleteEntity(int entityId)
    {
        for (auto iterator = Entities.begin(); iterator != Entities.end();)
        {
            Entity* currentEntity = *iterator;
            if (currentEntity->Id == entityId)
            {
                Entities.erase(iterator);
            }
            return;
        }
    }

    Entity* GetEntity(int entityId) const
    {
        for (size_t i = 0; i < Entities.size(); i++)
        {
            if (Entities[i]->Id == entityId)
            {
                return Entities[i];
            }
        }

        return nullptr;
    }

    bool IsEntityAlive(int entityId) const
    {
        Entity* entity = GetEntity(entityId);
        return entity != nullptr;
    }

    std::vector<Component> GetEntityComponents(int entityId)
    {
        return std::vector<Component>();
    }

    template<Derived<Component> TComponent>
    void AddComponent(int entityEd, TComponent component)
    {
        
    }

    template<Derived<Component> TComponent>
    void RemoveComponent(int entityId, TComponent component)
    {
        
    }

private:
    int _entityCount = 0;
};

class System
{
public:
    System(World world) : _world(world)
    {
        _world = world;
    }

    void virtual ProcessComponents();

protected:
    World _world;
};

class UiManager
{
public:
    int virtual ProcessInput();
    void virtual Render();
};

inline int Example()
{
    const World world;
    UiManager uiManger;
    System playerSystem(world);
    System collisionSystem(world);
    System renderSystem(world);

    while (true)
    {
        if (!uiManger.ProcessInput())
        {
            break;
        }

        playerSystem.ProcessComponents();
        collisionSystem.ProcessComponents();
        renderSystem.ProcessComponents();

        uiManger.Render();
    }

    return 0;
}