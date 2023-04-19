#pragma once

#include <vector>
#include "../engine/Component.h"
#include "../engine/System.h"

class Health : public Component
{
public:
    uint32_t HealthPoints;
};

class Damage: public Component
{
public:
    uint32_t DamagePoints;
};

class HealthSystem: public System
{
public:
    void ProcessComponents(std::vector<Component*> components) override
    {
        
    }
};