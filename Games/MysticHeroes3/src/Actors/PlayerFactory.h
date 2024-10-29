#pragma once

#include "../Assets/RoguesAssetUnits.h"
#include "../Systems/Actor.h"

class PlayerFactory
{
public:
    static Player* CreateMage()
    {
        Player* p = new Player();
        p->TileSetUnit = MaleWizard;
        p->Class = PlayerClass::MageClass;

        return p;
    }
};