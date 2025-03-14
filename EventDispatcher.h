#pragma once

#include "Delegate.h"


template<typename ReturnValue, typename... Arguments>
class EventDispatcher
{
public:
	EventDispatcher() = default;
	~EventDispatcher() { subscribedCallbacks.clear(); };

	void SubscribeCallback(Delegate<ReturnValue(Arguments...)>& delegate)
	{
		subscribedCallbacks.push_back(delegate);
	};

	void Call(Arguments... args)
	{
		for (const auto& callback : subscribedCallbacks)
		{
			callback(args...);
		}
	};

private:
	std::vector<Delegate<ReturnValue(Arguments...)>> subscribedCallbacks;
};

