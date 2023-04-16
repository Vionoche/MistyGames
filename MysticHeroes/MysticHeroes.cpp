#include <iostream>
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class Health : public Component
{
public:
    uint32_t HealthPoints;
    uint32_t PhysicalResist;
    uint32_t MagicResist;

    Health(
        int entityId,
        uint32_t healthPoints,
        uint32_t physicalResist,
        uint32_t magicResist)
        : Component(entityId), HealthPoints(healthPoints), PhysicalResist(physicalResist), MagicResist(magicResist)
    {
    }

    void PrintName() const override
    {
        std::cout << "Health Component EntityId = " << EntityId << std::endl;
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
    uint32_t DamagePoints;
    bool IsMagic;

    AttackDamage(int entityId, uint32_t damagePoints, bool isMagic)
        : Component(entityId), DamagePoints(damagePoints), IsMagic(isMagic)
    {
    }
};

Entity* CreateMonster(
    const int entityId,
    const char* name,
    const uint32_t healthPoints,
    const uint32_t physicalResist,
    const uint32_t magicResist)
{
    Entity* monster = new Entity(entityId, name);

    return monster;
}

Entity* CreatePlayer(const int entityId)
{
    Entity* player = new Entity(entityId, "Player");
    player->Components.push_back(std::make_shared<Health>(entityId, 100, 0, 0));

    return player;
}

int main()
{
    
}
