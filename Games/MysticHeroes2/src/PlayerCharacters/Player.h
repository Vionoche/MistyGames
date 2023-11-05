#pragma once

#include <cstdint>

#include "../Engine/InputState.h"
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
        AddNode(new Health("Health", 1000, 0.0f, 0.0f));
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

    void Process() override;

    void Draw() override;

protected:
    uint32_t _characterExperiencePoints = 0;
};
