#pragma once

#include <vector>

template<class T>
class Subscription;

template<class T>
class IObserver;

template<class T>
class Observable;


template<class T>
class Observable
{
public:
    Subscription<T>* Subscribe(IObserver<T>* observer)
    {
        _observers.push_back(observer);

        Subscription<T>* subscription = new Subscription<T>(this, observer);

        return subscription;
    }

    void Unsubscribe(const IObserver<T>* observer)
    {
        for (auto iterator = _observers.begin(); iterator != _observers.end();)
        {
            if (const IObserver<T>* item = *iterator; item == observer)
            {
                iterator = _observers.erase(iterator);
                continue;
            }
            ++iterator;
        }
    }

    void Emit(const T dataPointer) const
    {
        for (const auto observer : _observers)
        {
            observer->OnNext(dataPointer);
        }
    }

    uint64_t GetSubscribersCount() const
    {
        return _observers.size();
    }

protected:
    std::vector<IObserver<T>*> _observers;
};


template<class T>
class IObserver
{
public:
    virtual void OnNext(const T dataPointer) { }

    virtual ~IObserver() = default;
};


template<class T>
class Subscription
{
public:
    Subscription(Observable<T>* signal, IObserver<T>* observer)
        : _signal(signal), _observer(observer)
    {
    }

    ~Subscription()
    {
        if (_signal && _observer)
        {
            _signal->Unsubscribe(_observer);
            delete _observer;
        }
    }

private:
    Observable<T>* _signal;
    IObserver<T>* _observer;
};