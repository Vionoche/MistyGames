#pragma once

#include <vector>

#include "../Components/AttackDamage.h"
#include "../Components/TakenDamage.h"
#include "../Engine/Entity.h"
#include "../Engine/Component.h"
#include "../Engine/System.h"

class AttackSystemBase : public ISystem
{
protected:
    static void ProcessEntityAttack(const Entity& attacker, Entity& defender)
    {
        const AttackDamage* attackDamage = FindComponent<AttackDamage>(attacker.Components);
        if (!attackDamage)
        {
            return;
        }

        if (attackDamage->PhysicalDamage == 0 && attackDamage->MagicDamage == 0)
        {
            return;
        }

        defender.Components.push_back(
            std::make_shared<TakenDamage>(defender.EntityId, attackDamage->PhysicalDamage, attackDamage->MagicDamage));

        std::cout << attacker.EntityName
            << " hits " << attackDamage->PhysicalDamage << " physical and "
            << attackDamage->MagicDamage << " magic damage to "
            << defender.EntityName << std::endl;
    }
};
