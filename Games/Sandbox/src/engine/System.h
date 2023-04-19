#pragma once

#include <vector>
#include "Component.h"

class System
{
public:
    void virtual ProcessComponents(std::vector<Component*> components);
};
