#include <iostream>
#include <memory>
#include <vector>

#include "Component.h"

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

class Experience : public Component
{
public:
    uint32_t ExperiencePoints;

    Experience(int entityId, uint32_t experiencePoints)
        : Component(entityId), ExperiencePoints(experiencePoints)
    {
    }
};

class ExperienceForKill : public Component
{
public:
    uint32_t ExperiencePoints;

    ExperienceForKill(int entityId, uint32_t experiencePoints)
        : Component(entityId), ExperiencePoints(experiencePoints)
    {
    }
};

class Damage : public Component
{
public:
    int AttackerId;
    uint32_t DamagePoints;
    bool IsMagic;

    Damage(int entityId, int attackerId, uint32_t damagePoints, bool isMagic)
        : Component(entityId), AttackerId(attackerId), DamagePoints(damagePoints), IsMagic(isMagic)
    {
    }
};

int main()
{
    std::vector<std::shared_ptr<Component>> components;

    components.push_back(std::make_shared<Health>(11, 150, 0, 0));
    components.push_back(std::make_shared<Experience>(11, 0));
    components.push_back(std::make_shared<ExperienceForKill>(11, 1500));

    components.push_back(std::make_shared<Health>(12, 200, 0, 0));
    components.push_back(std::make_shared<Experience>(12, 0));
    components.push_back(std::make_shared<ExperienceForKill>(12, 2000));

    components.push_back(std::make_shared<Health>(13, 10, 0, 0));
    components.push_back(std::make_shared<Experience>(13, 0));
    components.push_back(std::make_shared<ExperienceForKill>(13, 100));

    components.push_back(std::make_shared<Health>(14, 25, 0, 0));
    components.push_back(std::make_shared<Experience>(14, 0));
    components.push_back(std::make_shared<ExperienceForKill>(14, 250));

    components.push_back(std::make_shared<Health>(15, 5, 0, 0));
    components.push_back(std::make_shared<Experience>(15, 0));
    components.push_back(std::make_shared<ExperienceForKill>(15, 50));

    // Damage system
    for (int index = 0; index < static_cast<int>(components.size()); index++)
    {
        std::shared_ptr<Component> component = components[index];

        component->PrintName();
    }
}
