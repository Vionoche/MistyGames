#pragma once

#include <iostream>
#include <string>

#include "Signals.h"

struct ModelDto
{
    int X;
    int Y;
    std::string Description;
};

class FloatListener : public IObserver<float>
{
public:
    FloatListener(const char* name) : _name(name)
    {
        std::cout << "FloatListener " << _name << " was created" << std::endl;
    }

    void OnNext(const float dataPointer) override
    {
        std::cout << _name << ": Float data " << dataPointer << " was received" << std::endl;
    }

    ~FloatListener() override
    {
        std::cout << "FloatListener " << _name << " was destroyed" << std::endl;
    }

private:
    std::string _name;
};

class StringListener : public IObserver<const char*>
{
public:
    StringListener(const char* name) : _name(name)
    {
        std::cout << "StringListener " << _name << " was created" << std::endl;
    }

    void OnNext(const char* dataPointer) override
    {
        std::cout << "String data " << dataPointer << " was received" << std::endl;
    }

    ~StringListener() override
    {
        std::cout << "StringListener " << _name << " was destroyed" << std::endl;
    }

private:
    std::string _name;
};

class ModelDtoListener : public IObserver<ModelDto*>
{
public:
    ModelDtoListener(const char* name) : _name(name)
    {
        std::cout << "ModelDtoListener " << _name << " was created" << std::endl;
    }

    void OnNext(ModelDto* const dataPointer) override
    {
        std::cout << "ModelDto data X:" << dataPointer->X << " Y:" << dataPointer->Y << " Description: " << dataPointer->Description << " was received" << std::endl;
    }

    ~ModelDtoListener() override
    {
        std::cout << "ModelDtoListener " << _name << " was destroyed" << std::endl;
    }

private:
    std::string _name;
};

static void TestSignals()
{
    Observable<float> floatSignal;
    Observable<const char*> stringSignal;
    Observable<ModelDto*> modelDtoSignal;

    FloatListener* floatListener1 = new FloatListener("Mr. Float");
    FloatListener* floatListener2 = new FloatListener("Ms. Float");
    StringListener* stringListener = new StringListener("Bro String");
    ModelDtoListener* modelDtoListener = new ModelDtoListener("DTO");

    const auto subscription1 = floatSignal.Subscribe(floatListener1);
    const auto subscription2 = floatSignal.Subscribe(floatListener2);
    const auto subscription3 = stringSignal.Subscribe(stringListener);
    const auto subscription4 = modelDtoSignal.Subscribe(modelDtoListener);

    floatSignal.Emit(5.6f);
    floatSignal.Emit(50056.6889f);
    stringSignal.Emit("Boom");

    ModelDto* dto = new ModelDto();
    dto->X = 40;
    dto->Y = 100;
    dto->Description = "Okaaaay";

    modelDtoSignal.Emit(dto);

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