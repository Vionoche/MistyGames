#pragma once

#include <cstdint>

#include "../Engine/InputState.h"
#include "../Engine/Signals.h"
#include "../Engine/Node.h"
#include "../Nodes/Attack.h"
#include "../Nodes/CharacterName.h"
#include "../Nodes/Health.h"


class Player : public Node
{
public:
    Player(const char* nodeName)
        : Node(nodeName)
    {
        AddNode(new CharacterName(nodeName));

        const auto health = new Health("Health", 200, 0.5f, 0.25f);
        _healthOverSubscription = health->HealthOverObservable.Subscribe(
            new Listener(this, &Player::OnHealthOverHandler));
        AddNode(health);

        AddNode(new Attack("Attack", 20, 0));
    }

    void AddCharacterExperiencePoints(uint32_t experiencePoints)
    {
        _characterExperiencePoints += experiencePoints;
    }

    uint32_t GetCharacterExperiencePoints() const
    {
        return _characterExperiencePoints;
    }

    bool GetIsDead() const
    {
        return _isDead;
    }

    void Process() override;

    void Draw() override;

protected:
    uint32_t _characterExperiencePoints = 0;
    bool _isDead = false;
    Subscription<int>* _healthOverSubscription = nullptr;

    void OnHealthOverHandler(int healthPoints);
};
