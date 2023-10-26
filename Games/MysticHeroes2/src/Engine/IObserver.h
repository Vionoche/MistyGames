#pragma once

class IObserver
{
public:
    virtual void OnNext(const void* dataPointer) { }

    virtual ~IObserver() = default;
};