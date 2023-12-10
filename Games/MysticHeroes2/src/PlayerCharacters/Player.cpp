#include "../Engine/InputState.h"
#include "../Monsters/Monster.h"
#include "../Nodes/Attack.h"
#include "../Nodes/CharacterLevel.h"
#include "../Nodes/CharacterName.h"
#include "../Nodes/Health.h"
#include "Player.h"

Player::Player(const char* nodeName): ConsolePrinter(nodeName)
{
    AddNode(new CharacterName(nodeName));

    const auto health = new Health("Health", 200, 0.5f, 0.25f);
    _healthOverSubscription = health->HealthOverObservable.Subscribe(
        new Listener(this, &Player::OnHealthOverHandler));
    AddNode(health);

    AddNode(new Attack("Attack", 20, 0));

    const auto characterLevel = new CharacterLevel("CharacterLevel");
    _characterLevelSubscription = characterLevel->LevelUpObservable.Subscribe(
        new Listener(this, &Player::OnLevelUpHandler));
    AddNode(characterLevel);
}

void Player::AddCharacterExperiencePoints(const uint32_t experiencePoints) const
{
    if (const auto characterLevel = FindNode<CharacterLevel>(_nodes))
    {
        characterLevel->AddExperiencePoints(experiencePoints);
    }
}

bool Player::GetIsDead() const
{
    return _isDead;
}

PlayerModel Player::SavePlayer() const
{
    const auto health = FindNode<Health>(_nodes);
    const auto attack = FindNode<Attack>(_nodes);
    const auto characterLevel = FindNode<CharacterLevel>(_nodes);

    const PlayerModel model
    {
        health->GetHealthPoints(),
        health->GetPhysicalResist(),
        health->GetMagicResist(),
        attack->GetPhysicalDamage(),
        attack->GetMagicDamage(),
        characterLevel->GetCurrentLevel(),
        characterLevel->GetExperiencePoints()
    };

    return model;
}

void Player::LoadPlayer(const PlayerModel& playerModel) const
{
    const auto health = FindNode<Health>(_nodes);
    const auto attack = FindNode<Attack>(_nodes);
    const auto characterLevel = FindNode<CharacterLevel>(_nodes);

    health->Update(playerModel.HealthPoints, playerModel.PhysicalResist, playerModel.MagicResist);
    attack->UpdateDamage(playerModel.PhysicalDamage, playerModel.MagicDamage);
    characterLevel->Update(playerModel.CurrentLevel, playerModel.ExperiencePoints);
}



void Player::Process()
{
    if (_isDead)
    {
        return;
    }

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

    if (_isDead)
    {
        std::cout << " is dead" << std::endl;
        return;
    }

    if (const auto health = (Health*)GetNode("Health"))
    {
        std::cout << " HP " << health->GetHealthPoints();
    }

    if (const auto characterLevel = (CharacterLevel*)GetNode("CharacterLevel"))
    {
        std::cout << " Level " << characterLevel->GetCurrentLevel();
        std::cout << " Exp " << characterLevel->GetExperiencePoints() << std::endl;
    }
}

void Player::OnHealthOverHandler(int healthPoints)
{
    _isDead = true;
}

void Player::OnLevelUpHandler(const uint32_t newLevel)
{
    if (const auto attack = FindNode<Attack>(_nodes))
    {
        attack->UpdateDamage(20 + (2 * newLevel), 0);
    }

    if (const auto health = FindNode<Health>(_nodes))
    {
        health->UpdateHealthPoints(200 + (10 * (int)newLevel));
    }

    std::cout << "Level Up!" << std::endl;
}
