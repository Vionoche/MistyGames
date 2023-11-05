#include "../Monsters/Monster.h"
#include "Player.h"

void Player::Process()
{
    const int inputCode = InputState::GetInstance().GetInputCode();
    if (inputCode <= 0)
    {
        return;
    }

    const auto monsters = FindNodes<Monster>(_parent->GetNodes());
    for (const auto monster : monsters)
    {
        if (monster->GetMonsterId() == inputCode)
        {
            if (const auto attack = FindNode<Attack>(_nodes))
            {
                attack->MakeDamage(monster);
                break;
            }
        }
    }
}

void Player::Draw()
{
    if (const auto characterName = FindNode<CharacterName>(_nodes))
    {
        std::cout << characterName->GetName();
    }
    else
    {
        std::cout << "Undefined";
    }

    if (const auto health = (Health*)GetNode("Health"))
    {
        std::cout << " HP " << health->GetHealthPoints();
    }

    std::cout << " Exp " << _characterExperiencePoints << std::endl;
}
