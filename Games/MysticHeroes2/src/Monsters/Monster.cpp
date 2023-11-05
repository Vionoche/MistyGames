#include "../PlayerCharacters/Player.h"
#include "Monster.h"

void Monster::Process()
{
    const auto attack = FindNode<Attack>(_nodes);
    const auto player = FindNode<Player>(_parent->GetNodes());

    if (attack && player)
    {
        attack->MakeDamage(player);
    }
}

void Monster::Draw()
{
    const auto characterName = FindNode<CharacterName>(_nodes);
    if (characterName == nullptr)
    {
        std::cout << _nodeName << " doesn't have any name" << std::endl;
        return;
    }

    std::cout << characterName->GetName() << " (" << _monsterId << ")";

    if (const auto health = (Health*)GetNode("Health"))
    {
        std::cout << " HP " << health->GetHealthPoints() << std::endl;
    }
}

void Monster::OnHealthOverHandler(int healthPoints)
{
    if (auto player = FindNode<Player>(_parent->GetNodes()))
    {
        player->AddCharacterExperiencePoints(_rewardExperiencePoints);
    }

    QueueToDelete();
}
