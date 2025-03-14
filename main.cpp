
#include <iostream>

#include "EventDispatcher.h"

//extern EventDispatcher<void()>* dispatcher;
//
//EventDispatcher<void()>* dispatcher = nullptr;

class Foo
{
public:
    Foo(int newVal) : value(newVal)
    {
    };
    ~Foo() = default;

    void TriggeredVoid()
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

int main()
{
    //dispatcher = new  EventDispatcher<void()>();

    Foo foo(1);

    std::function<void(void)> function1 = [&foo](void) {foo.TriggeredVoid(); };
    std::function<void(int)> function2 = [&foo](int x) {foo.Triggered(x); };
    std::function<void(int, int)> function3 = [&foo](int x, int y) {foo.Triggered(x, y); };
    std::function<void(int, int)> function4 = [&foo](int x, int y) {foo.Triggered(x, y); };

    Delegate<void, int, int> delegate([&foo](int x, int y) {foo.Triggered(x, y); });
    Delegate<void, int, int> delegate2([&foo](int x, int y) {foo.Triggered(x, y); });
    Delegate<void> delegateVoid(function1);
    Delegate<void> delegateVoid2([&foo](void) {foo.TriggeredVoid(); });

    delegate(1, 2);
    delegate2(3, 4);
    delegateVoid();
    delegateVoid2();

    //dispatcher->Call();

    //delete dispatcher;
}
