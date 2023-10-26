#pragma once

#include <string>
#include <vector>

#include "IObserver.h"
#include "Observable.h"
#include "Subscription.h"

void TestObservables();

struct ModelDto
{
    int X;
    int Y;
    std::string Description;
};

class FloatListener : public IObserver
{
public:
    FloatListener(const char * name) : _name(name)
    {
        std::cout << "FloatListener " << _name << " was created" << std::endl;
    }

    void OnNext(const void* dataPointer) override
    {
        const float* data = (const float*)dataPointer;

        std::cout << "Float data " << *data << " was received" << std::endl;
    }

    ~FloatListener() override
    {
        std::cout << "FloatListener " << _name << " was destroyed" << std::endl;
    }

private:
    std::string _name;
};

class StringListener : public IObserver
{
public:
    StringListener(const char * name) : _name(name)
    {
        std::cout << "StringListener " << _name << " was created" << std::endl;
    }

    void OnNext(const void* dataPointer) override
    {
        const char* stringData = (const char*)dataPointer;

        std::cout << "String data " << stringData << " was received" << std::endl;
    }

    ~StringListener() override
    {
        std::cout << "StringListener " << _name << " was destroyed" << std::endl;
    }

private:
    std::string _name;
};

class ModelDtoListener : public IObserver
{
public:
    ModelDtoListener(const char* name) : _name(name)
    {
        std::cout << "ModelDtoListener " << _name << " was created" << std::endl;
    }

    void OnNext(const void* dataPointer) override
    {
        const ModelDto* stringData = (const ModelDto*)dataPointer;

        std::cout << "ModelDto data X:" << stringData->X << " Y:" << stringData->Y << " Description: " << stringData->Description << " was received" << std::endl;
    }

    ~ModelDtoListener() override
    {
        std::cout << "ModelDtoListener " << _name << " was destroyed" << std::endl;
    }

private:
    std::string _name;
};

void TestObservables()
{
    Observable floatSignal;
    Observable stringSignal;
    Observable modelDtoSignal;

    FloatListener* floatListener1 = new FloatListener("Mr. Float");
    FloatListener* floatListener2 = new FloatListener("Ms. Float");
    StringListener* stringListener = new StringListener("Bro String");
    ModelDtoListener* modelDtoListener = new ModelDtoListener("DTO");

    const Subscription* subscription1 = floatSignal.Subscribe(floatListener1);
    const Subscription* subscription2 = floatSignal.Subscribe(floatListener2);
    const Subscription* subscription3 = stringSignal.Subscribe(stringListener);
    const Subscription* subscription4 = modelDtoSignal.Subscribe(modelDtoListener);

    const float* value1 = new float(5.6f);
    const float* value2 = new float(50056.6889f);

    floatSignal.Emit(value1);
    floatSignal.Emit(value2);
    stringSignal.Emit("Boom");

    ModelDto* dto = new ModelDto();
    dto->X = 40;
    dto->Y = 100;
    dto->Description = "Okaaaay";

    modelDtoSignal.Emit(dto);

    delete value1;
    delete value2;

    std::cout << "floatSignal" << " subscriptions count: " << floatSignal.GetSubscribersCount() << std::endl;
    std::cout << "stringSignal" << " subscriptions count: " << stringSignal.GetSubscribersCount() << std::endl;
    std::cout << "modelDtoSignal" << " subscriptions count: " << modelDtoSignal.GetSubscribersCount() << std::endl;

    delete subscription1;
    std::cout << "floatSignal" << " subscriptions count: " << floatSignal.GetSubscribersCount() << std::endl;
    std::cout << "stringSignal" << " subscriptions count: " << stringSignal.GetSubscribersCount() << std::endl;
    std::cout << "modelDtoSignal" << " subscriptions count: " << modelDtoSignal.GetSubscribersCount() << std::endl;

    delete subscription2;
    std::cout << "floatSignal" << " subscriptions count: " << floatSignal.GetSubscribersCount() << std::endl;
    std::cout << "stringSignal" << " subscriptions count: " << stringSignal.GetSubscribersCount() << std::endl;
    std::cout << "modelDtoSignal" << " subscriptions count: " << modelDtoSignal.GetSubscribersCount() << std::endl;

    delete subscription3;
    std::cout << "floatSignal" << " subscriptions count: " << floatSignal.GetSubscribersCount() << std::endl;
    std::cout << "stringSignal" << " subscriptions count: " << stringSignal.GetSubscribersCount() << std::endl;
    std::cout << "modelDtoSignal" << " subscriptions count: " << modelDtoSignal.GetSubscribersCount() << std::endl;

    delete subscription4;
    std::cout << "floatSignal" << " subscriptions count: " << floatSignal.GetSubscribersCount() << std::endl;
    std::cout << "stringSignal" << " subscriptions count: " << stringSignal.GetSubscribersCount() << std::endl;
    std::cout << "modelDtoSignal" << " subscriptions count: " << modelDtoSignal.GetSubscribersCount() << std::endl;
}