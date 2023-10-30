#pragma once

#include <vector>

template<class T>
class SubscriptionTemplate;

template<class T>
class IObserverTemplate;

template<class T>
class ObservableTemplate;


template<class T>
class ObservableTemplate
{
public:
    SubscriptionTemplate<T>* Subscribe(IObserverTemplate<T>* observer)
    {
        _observers.push_back(observer);

        SubscriptionTemplate<T>* subscription = new SubscriptionTemplate<T>(this, observer);

        return subscription;
    }

    void Unsubscribe(const IObserverTemplate<T>* observer)
    {
        for (auto iterator = _observers.begin(); iterator != _observers.end();)
        {
            if (const IObserverTemplate<T>* item = *iterator; item == observer)
            {
                iterator = _observers.erase(iterator);
                continue;
            }
            ++iterator;
        }
    }

    void Emit(const T* dataPointer) const
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
    std::vector<IObserverTemplate<T>*> _observers;
};


template<class T>
class IObserverTemplate
{
public:
    virtual void OnNext(const T* dataPointer) { }

    virtual ~IObserverTemplate() = default;
};


template<class T>
class SubscriptionTemplate
{
public:
    SubscriptionTemplate(ObservableTemplate<T>* signal, IObserverTemplate<T>* observer)
        : _signal(signal), _observer(observer)
    {
    }

    ~SubscriptionTemplate()
    {
        if (_signal && _observer)
        {
            _signal->Unsubscribe(_observer);
            delete _observer;
        }
    }

private:
    ObservableTemplate<T>* _signal;
    IObserverTemplate<T>* _observer;
};