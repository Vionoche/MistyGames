#pragma once

#include "IObserver.h"

class Observable;

class Subscription
{
public:
    Subscription(Observable* signal, IObserver* observer);

    ~Subscription();

private:
    Observable* _signal;
    IObserver* _observer;
};
