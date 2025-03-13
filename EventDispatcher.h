#pragma once

#include <functional>
#include <vector>

template<typename ReturnValue, typename... Arguments>
class EventDispatcher
{
public:
	EventDispatcher() = default;
	~EventDispatcher() = default;

	void SubscribeCallback(const std::function<ReturnValue(Arguments...)>& functionCallback)
	{
		subscribedCallbacks.push_back(functionCallback);
	};

private:
	std::vector<std::function<ReturnValue(Arguments...)>> subscribedCallbacks;
};