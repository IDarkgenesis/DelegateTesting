#pragma once

#include <functional>
#include <vector>


template<typename ReturnValue, typename... Arguments>
class EventDispatcher
{
public:
	EventDispatcher() = default;
	~EventDispatcher() { subscribedCallbacks.clear(); };

	void SubscribeCallback(const std::function<ReturnValue(Arguments...)>& functionCallback)
	{
		subscribedCallbacks.push_back(functionCallback);
	};

	void Call(Arguments... args)
	{
		for (const auto& callback : subscribedCallbacks)
		{
			callback(args...);
		}
	};

private:
	std::vector<std::function<ReturnValue(Arguments...)>> subscribedCallbacks;
};

