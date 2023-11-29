#pragma once

#include <vector>

#include "Entity.h"


class ISystem
{
public:
    virtual int Process(std::vector<Entity*>& entities)
    {
        return 0;
    }

    virtual ~ISystem() = default;
};
