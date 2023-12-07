#pragma once

#include <cstdint>

#include "../Engine/Signals.h"
#include "../Engine/Node.h"
#include "../Nodes/Attack.h"
#include "../Nodes/CharacterLevel.h"
#include "../Nodes/CharacterName.h"
#include "../Nodes/ConsolePrinter.h"
#include "../Nodes/Health.h"


struct PlayerModel
{
    
};


class Player : public ConsolePrinter
{
public:
    Player(const char* nodeName)
        : ConsolePrinter(nodeName)
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

    void AddCharacterExperiencePoints(const uint32_t experiencePoints) const
    {
        if (const auto characterLevel = FindNode<CharacterLevel>(_nodes))
        {
            characterLevel->AddExperiencePoints(experiencePoints);
        }
    }

    bool GetIsDead() const
    {
        return _isDead;
    }

    PlayerModel SavePlayer();

    void LoadPlayer(PlayerModel playerModel);

    void Process() override;

    void Draw() override;

protected:
    bool _isDead = false;
    Subscription<int>* _healthOverSubscription = nullptr;
    Subscription<uint32_t>* _characterLevelSubscription = nullptr;

    void OnHealthOverHandler(int healthPoints);

    void OnLevelUpHandler(uint32_t newLevel);
};
