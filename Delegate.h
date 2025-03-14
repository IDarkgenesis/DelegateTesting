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
	};

	template<typename TLambda>
	Delegate(TLambda&& lambda)
	{
		std::function<ReturnValue(Arguments...)> temporalFunction = lambda;
		callback = std::move(temporalFunction);
	};

	~Delegate() = default;

	ReturnValue operator()(Arguments... args) 
	{
		callback(args...);
	}
	
private:
	std::function<ReturnValue(Arguments...)> callback;
};