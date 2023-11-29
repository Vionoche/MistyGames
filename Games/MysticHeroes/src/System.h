#pragma once

#include <vector>

#include "Entity.h"


class ISystem
{
public:
    virtual int Process(std::vector<Entity*>& entities);

    virtual ~ISystem() = default;
};
