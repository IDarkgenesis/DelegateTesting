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

	//template<typename TLambda>
	//Delegate(TLambda&& lambda)
	//{
	//	std::function<ReturnValue(Arguments...)> temporalFunction = lambda;
	//	callback = std::move(temporalFunction);
	//};

	~Delegate() = default;
	 
	//ReturnValue operator()(Arguments... args) 
	//{
	//	callback(args...);
	//}

	ReturnValue Call(Arguments... args)
	{
		callback(args...);
	}
	
private:
	std::function<ReturnValue(Arguments...)> callback;
};

//template<>
//class Delegate<void, void>
//{
//public:
//	Delegate(std::function<void(void)>& newCallback)
//	{
//		callback = std::move(newCallback);
//	};
//
//	Delegate(std::function<void(void)>&& newCallback)
//	{
//		callback = std::move(newCallback);
//	}
//
//	template<typename TLambda>
//	Delegate(TLambda&& lambda)
//	{
//		std::function<void(void)> temporalFunction = lambda;
//		callback = std::move(temporalFunction);
//	};
//
//	~Delegate() = default;
//
//	void operator()()
//	{
//		callback();
//	}
//
//private:
//	std::function<void(void)> callback;
//};