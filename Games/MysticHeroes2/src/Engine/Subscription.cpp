#include "Observable.h"
#include "Subscription.h"

Subscription::Subscription(Observable* signal, IObserver* observer) : _signal(signal), _observer(observer)
{
}

Subscription::~Subscription()
{
    if (_signal && _observer)
    {
        _signal->Unsubscribe(_observer);
        delete _observer;
    }
}
