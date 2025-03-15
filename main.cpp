
#include <iostream>

#include "EventDispatcher.h"

extern EventDispatcher<void>* dispatcher;

EventDispatcher<void>* dispatcher = nullptr;

class Foo
{
public:
	Foo(int newVal) : value(newVal)
	{
		std::function<void(void)> function = std::bind(&Foo::TriggeredVoid, this);
		Delegate<void> delegate(function);
		callbackID = dispatcher->SubscribeCallback(std::move(delegate));
	};
	~Foo() = default;

	void TriggeredVoid()
	{
		std::cout << "A triggered " << value << std::endl;
	};

	void Triggered(int first)
	{
		std::cout << "A triggered " << first << std::endl;
	};

	void Triggered(int first, int second)
	{
		std::cout << "A triggered " << first << second << std::endl;
	};

	int Sum(int x, int y) 
	{ 
		int result = x + y;
		std::cout << "The result is " << result << std::endl; 

		return result;
	}

private:
	int value = 0;
	int callbackID = -1;
};

int main()
{
	dispatcher = new EventDispatcher<void>();
	EventDispatcher<void, int, int> intDispatcher;
	EventDispatcher<int, int, int> intDispatcher2;

	Foo foo(1);

	std::function<void(void)> function1 = [&foo](void) {foo.TriggeredVoid(); };

	Delegate<void, int, int> delegate([&foo](int x, int y) {foo.Triggered(x, y); });
	Delegate<void, int, int> delegate2([&foo](int x, int y) {foo.Triggered(x, y); });
	Delegate<void> delegateVoid(function1);
	Delegate<void> delegateVoid2([&foo](void) {foo.TriggeredVoid(); });

	Delegate<int, int, int> delegateInt2([&foo](int x, int y) { return foo.Sum(x, y); });

	std::cout << "----- START SINGLE DELEGATES -----\n";

	delegate.Call(1, 2);
	delegate2.Call(3, 4);
	delegateVoid.Call();
	delegateVoid2.Call();

	int delegateResult = delegateInt2.Call(1, 2);

	std::cout << "----- END SINGLE DELEGATES -----\n";

	std::cout << "----- START VOID DISPATCHER -----\n";

	int callbackID = dispatcher->SubscribeCallback(std::move(delegateVoid));
	dispatcher->Call();
	std::cout << "Removing one callback\n";

	dispatcher->RemoveCallback(callbackID);
	dispatcher->Call();

	std::cout << "----- END VOID DISPATCHER -----\n";

	std::cout << "----- START INT DISPATCHER -----\n";

	intDispatcher2.SubscribeCallback(std::move(delegateInt2));
	intDispatcher2.Call(3, 5);

	int intID1 = intDispatcher.SubscribeCallback(std::move(delegate));
	int intID2 = intDispatcher.SubscribeCallback(std::move(delegate2));
	intDispatcher.Call(1, 2);

	std::cout << "Removing one callback\n";

	intDispatcher.RemoveCallback(intID2);
	intDispatcher.Call(0, 0);

	std::cout << "----- END INT DISPATCHER -----\n";

	delete dispatcher;
}
