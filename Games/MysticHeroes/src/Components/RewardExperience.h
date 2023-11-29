#pragma once

#include "../Engine/Component.h"

class RewardExperience : public Component
{
public:
    uint32_t ExperiencePoints;

    RewardExperience(int entityId, uint32_t experiencePoints)
        : Component(entityId), ExperiencePoints(experiencePoints)
    {
    }
};
