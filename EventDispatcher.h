#pragma once

#include "Delegate.h"
#include <list>

template<typename ReturnValue, typename... Arguments>
class EventDispatcher
{
public:

	EventDispatcher() = default;
	~EventDispatcher() { subscribedCallbacks.clear(); };


	void SubscribeCallback(Delegate<ReturnValue, Arguments...>&& delegate)
	{
		subscribedCallbacks.push_back(std::move(delegate));
	};

	void Call(Arguments... args)
	{
		for (auto callback : subscribedCallbacks)
		{
			callback.Call(args...);
		}
	};

private:
	std::list<Delegate<ReturnValue, Arguments...>> subscribedCallbacks;
};

template<>
class EventDispatcher<void>
{
public:
	EventDispatcher() = default;
	~EventDispatcher() { subscribedCallbacks.clear(); };


	void SubscribeCallback(Delegate<void>&& delegate)
	{
		subscribedCallbacks.push_back(std::move(delegate));
	};

	void Call()
	{
		for (auto callback : subscribedCallbacks)
		{
			callback.Call();
		}
	};

private:
	std::list<Delegate<void>> subscribedCallbacks;
};