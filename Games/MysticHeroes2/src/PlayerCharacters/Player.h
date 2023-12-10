#pragma once

#include <cstdint>

#include "../Engine/Signals.h"
#include "../Nodes/ConsolePrinter.h"


struct PlayerModel
{
    int HealthPoints;
    float PhysicalResist;
    float MagicResist;
    uint32_t PhysicalDamage;
    uint32_t MagicDamage;
    uint32_t CurrentLevel;
    uint32_t ExperiencePoints;
};


class Player : public ConsolePrinter
{
public:
    Player(const char* nodeName);

    void AddCharacterExperiencePoints(uint32_t experiencePoints) const;

    bool GetIsDead() const;

    PlayerModel SavePlayer() const;

    void LoadPlayer(const PlayerModel& playerModel) const;

    void Process() override;

    void Draw() override;

protected:
    bool _isDead = false;
    Subscription<int>* _healthOverSubscription = nullptr;
    Subscription<uint32_t>* _characterLevelSubscription = nullptr;

    void OnHealthOverHandler(int healthPoints);

    void OnLevelUpHandler(uint32_t newLevel);
};
