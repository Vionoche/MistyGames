#pragma once

#include "../Assets/TileSetUnit.h"

class Actor
{
public:
    TileSetUnit TileSetUnit;
    bool IsMouseHovered = false;

    virtual ~Actor() {}
};

enum MonsterClass
{
    SkeletonClass,
    SkeletonArcherClass
};

class Monster : public Actor
{
public:
    MonsterClass Class = MonsterClass::SkeletonClass;
    int Health = 20;
    int Mana = 0;
    int ExperienceReward = 10;
    int Level = 1;
    int BaseDamage = 5;
};

enum PlayerClass
{
    FighterClass,
    MageClass,
    ArcherClass
};

class Player : public Actor
{
public:
    PlayerClass Class = PlayerClass::FighterClass;
    int Health = 100;
    int Mana = 0;
    int Experience = 0;
    int Level = 1;
    int BaseDamage = 10;
};