#pragma once

#include <vector>

#include "IObserver.h"

class Subscription;

class Observable
{
public:
    Subscription* Subscribe(IObserver* observer);

    void Unsubscribe(const IObserver* observer);

    void Emit(const void* dataPointer) const;

    uint64_t GetSubscribersCount() const;

protected:
    std::vector<IObserver*> _observers;
};
