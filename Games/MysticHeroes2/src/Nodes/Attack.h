#pragma once

#include "CharacterName.h"
#include "Health.h"
#include "../Engine/Node.h"

class Attack : public Node
{
public:
    Attack(const char* nodeName, uint32_t physicalDamage, uint32_t magicDamage)
        : Node(nodeName),
          _physicalDamage(physicalDamage),
          _magicDamage(magicDamage)
    {
    }

    uint32_t GetPhysicalDamage() const
    {
        return _physicalDamage;
    }

    uint32_t GetMagicDamage() const
    {
        return _magicDamage;
    }

    void MakeDamage(const Node* target) const
    {
        const auto targetNodes = target->GetNodes();
        const auto health = FindNode<Health>(targetNodes);

        if (health == nullptr)
        {
            return;
        }

        const auto targetName = FindNode<CharacterName>(targetNodes);
        const auto attackerName = FindNode<CharacterName>(_parent->GetNodes());

        if (targetName && attackerName)
        {
            std::cout << attackerName->GetName()
                << " hits " << _physicalDamage << " physical and "
                << _magicDamage << " magic damage to "
                << targetName->GetName() << std::endl;
        }

        health->TakeDamage(_physicalDamage, _magicDamage);
    }

private:
    uint32_t _physicalDamage;
    uint32_t _magicDamage;
};