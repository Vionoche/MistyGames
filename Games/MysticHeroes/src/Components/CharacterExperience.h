#pragma once

#include "../Engine/Component.h"

class CharacterExperience : public Component
{
public:
    uint32_t ExperiencePoints;

    CharacterExperience(int entityId, uint32_t experiencePoints)
        : Component(entityId), ExperiencePoints(experiencePoints)
    {
    }
};