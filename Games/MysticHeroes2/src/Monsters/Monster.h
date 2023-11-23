#pragma once

#include "../Engine/Node.h"
#include "../Engine/Signals.h"
#include "../Nodes/Attack.h"
#include "../Nodes/CharacterName.h"
#include "../Nodes/ConsolePrinter.h"
#include "../Nodes/Health.h"


class Monster : public ConsolePrinter
{
public:
    Monster(
        const int monsterId,
        const char* monsterTitle,
        const int healthPoints,
        const float physicalResist,
        const float magicResist,
        const uint32_t physicalDamage,
        const uint32_t magicDamage,
        const uint32_t rewardExperiencePoints)
        : ConsolePrinter(std::string(monsterTitle + std::to_string(monsterId)).c_str()),
          _monsterId(monsterId),
          _rewardExperiencePoints(rewardExperiencePoints)
    {
        AddNode(new CharacterName(monsterTitle));

        const auto health = new Health("Health", healthPoints, physicalResist, magicResist);
        _healthOverSubscription = health->HealthOverObservable.Subscribe(
            new Listener(this, &Monster::OnHealthOverHandler));
        AddNode(health);

        AddNode(new Attack("Attack", physicalDamage, magicDamage));
    }

    int GetMonsterId() const
    {
        return _monsterId;
    }

    void Process() override;

    void Draw() override;

    ~Monster() override
    {
        delete _healthOverSubscription;
    }

protected:
    int _monsterId;
    uint32_t _rewardExperiencePoints;
    Subscription<int>* _healthOverSubscription = nullptr;

    void OnHealthOverHandler(int healthPoints);
};
