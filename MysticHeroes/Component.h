#pragma once

#include <iostream>

class Component
{
public:
    int EntityId;

    Component(int entityId) : EntityId(entityId)
    {
    }

    Component(const Component& other) : EntityId(other.EntityId)
    {
        std::cout << "Component for EntityId =" << EntityId << " was copied" << std::endl;
    }

    void virtual PrintName() const
    {
        std::cout << "Base Component for EntityId = " << EntityId << std::endl;
    }

    virtual ~Component()
    {
        std::cout << "Component for EntityId = " << EntityId << " was destroyed" << std::endl;
    }
};

class Health : public Component
{
public:
    int HealthPoints;
    float PhysicalResist;
    float MagicResist;

    Health(
        int entityId,
        int healthPoints,
        float physicalResist,
        float magicResist)
        : Component(entityId), HealthPoints(healthPoints), PhysicalResist(physicalResist), MagicResist(magicResist)
    {
    }

    void PrintName() const override
    {
        std::cout << "Health Component EntityId = " << EntityId << std::endl;
    }
};

class Player : public Component
{
public:
    Player(int entityId) : Component(entityId)
    {
    }
};

class Monster : public Component
{
public:
    Monster(int entityId) : Component(entityId)
    {
    }
};

class CharacterExperience : public Component
{
public:
    uint32_t ExperiencePoints;

    CharacterExperience(int entityId, uint32_t experiencePoints)
        : Component(entityId), ExperiencePoints(experiencePoints)
    {
    }
};

class RewardExperience : public Component
{
public:
    uint32_t ExperiencePoints;

    RewardExperience(int entityId, uint32_t experiencePoints)
        : Component(entityId), ExperiencePoints(experiencePoints)
    {
    }
};

class AttackDamage : public Component
{
public:
    uint32_t PhysicalDamage;
    uint32_t MagicDamage;

    AttackDamage(int entityId, uint32_t physicalDamage, uint32_t magicDamage)
        : Component(entityId), PhysicalDamage(physicalDamage), MagicDamage(magicDamage)
    {
    }
};

class TakenDamage : public Component
{
public:
    uint32_t PhysicalDamage;
    uint32_t MagicDamage;

    TakenDamage(int entityId, uint32_t physicalDamage, uint32_t magicDamage)
        : Component(entityId), PhysicalDamage(physicalDamage), MagicDamage(magicDamage)
    {
    }
};