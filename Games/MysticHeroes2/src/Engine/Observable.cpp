#include "Observable.h"
#include "Subscription.h"

Subscription* Observable::Subscribe(IObserver* observer)
{
    _observers.push_back(observer);

    Subscription* subscription = new Subscription(this, observer);

    return subscription;
}

void Observable::Unsubscribe(const IObserver* observer)
{
    for (auto iterator = _observers.begin(); iterator != _observers.end();)
    {
        if (const IObserver* item = *iterator; item == observer)
        {
            iterator = _observers.erase(iterator);
            continue;
        }
        ++iterator;
    }
}

void Observable::Emit(const void* dataPointer) const
{
    for (const auto observer : _observers)
    {
        observer->OnNext(dataPointer);
    }
}

uint64_t Observable::GetSubscribersCount() const
{
    return _observers.size();
}
