// DelegateTesting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "EventDispatcher.h"

class A
{
public:
    A(int newVal) : value(newVal) {};
    ~A() = default;

    void Triggered()
    {
        std::cout << "A triggered " << value << std::endl;
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
    A classA(1);
    B classB(2);

    std::function<void(void)> aTrigger = [&classA]() {classA.Triggered(); };

    EventDispatcher<void, void> voidDispatcher;

    voidDispatcher.SubscribeCallback(aTrigger);

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
