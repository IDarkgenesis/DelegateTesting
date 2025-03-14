#pragma once

#include <functional>

template<typename ReturnValue, typename... Arguments>
class Delegate 
{
public:
	Delegate(std::function<ReturnValue(Arguments...)>& newCallback)
	{
		callback = std::move(newCallback);
	};

	Delegate(std::function<ReturnValue(Arguments...)>&& newCallback) 
	{
		callback = std::move(newCallback);
	}

	~Delegate() = default;

	ReturnValue Call(Arguments... args)
	{
		callback(args...);
	}
	
private:
	std::function<ReturnValue(Arguments...)> callback;
};

