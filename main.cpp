// DelegateTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "EventDispatcher.h"

extern EventDispatcher<void>* dispatcher;

EventDispatcher<void>* dispatcher = nullptr;

class A
{
public:
    A(int newVal) : value(newVal) 
    {
        std::function<void(void)> triggerCallback = std::bind(&A::TriggeredV, this);
        dispatcher->SubscribeCallback(triggerCallback);
    };
    ~A() = default;

    void TriggeredV()
    {
        std::cout << "A triggered " << value << std::endl;
    };

    void Triggered(int asd)
    {
        std::cout << "A triggered " << asd << std::endl;
    };

    void Triggered(int asd, int dos)
    {
        std::cout << "A triggered " << asd << dos << std::endl;
    };

private:
    int value = 0;
};

class B
{
public:
    B(int newVal) : value(newVal) {};
    ~B() = default;

    void Triggered()
    {
        std::cout << "B triggered" << value << std::endl;
    };

private:
    int value = 0;
};

int main()
{
    dispatcher = new  EventDispatcher<void>();

    A classA(1);
    B classB(2);

    std::function<void(void)> aTrigger = [&classA](void) {classA.TriggeredV(); };
    std::function<void(int)> aTrigger2 = [&classA](int x) {classA.Triggered(x); };
    std::function<void(int, int)> aTrigger3 = [&classA](int x, int y) {classA.Triggered(x, y); };

    EventDispatcher<void, int> intDispatcher;
    EventDispatcher<void, int, int> d2;

    intDispatcher.SubscribeCallback(aTrigger2);
    intDispatcher.Call(2);

    d2.SubscribeCallback(aTrigger3);
    d2.Call(2,3);

    dispatcher->SubscribeCallback(aTrigger);
    dispatcher->Call();

    delete dispatcher;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
