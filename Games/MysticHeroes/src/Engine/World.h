#pragma once

class World
{
public:
    World() = default;

    World(const World& other) = delete;

    void operator=(World const&) = delete;

    virtual int Process()
    {
        return 0;
    }

    virtual ~World() = default;
};