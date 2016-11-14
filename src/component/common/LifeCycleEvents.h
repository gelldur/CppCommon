//
// Created by Dawid Drozd aka Gelldur on 13/11/16.
//

#pragma once

#include <type_traits>
#include <functional>

#include <Notification.h>
#include <EventCollector.h>
#include <component/ComponentManager.h>

namespace Dexode
{
namespace Component
{
MAKE_NOTIFICATION(OnEnter);

MAKE_NOTIFICATION(OnExit);

template<typename T>
struct has_onEnter
{
private:
	template<typename U>
	static auto test(int) -> decltype(std::declval<U>().onEnter(), std::true_type{});

	template<typename>
	static std::false_type test(...);

public:
	static const bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template<typename T>
typename std::enable_if<has_onEnter<T>::value, std::function<void()>>::type get_onEnter(T* value)
{
	return [value]()
	{
		value->onEnter();
	};
}

template<typename T>
typename std::enable_if<has_onEnter<T>::value == false, std::function<void()>>::type get_onEnter(T* value)
{
	return {};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct has_onExit
{
private:
	template<typename U>
	static auto test(int) -> decltype(std::declval<U>().onExit(), std::true_type{});

	template<typename>
	static std::false_type test(...);

public:
	static const bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template<typename T>
typename std::enable_if<has_onExit<T>::value, std::function<void()>>::type get_onExit(T* value)
{
	return [value]()
	{
		value->onExit();
	};
}

template<typename T>
typename std::enable_if<has_onExit<T>::value == false, std::function<void()>>::type get_onExit(T* value)
{
	return {};
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<class T>
EventCollector listenForOnEnterOnExit(T* component)
{
	static_assert(std::is_base_of<Base, T>::value, "T must inherit from Base component");
	EventCollector collector{component->getOwner()->getBus()};
	collector.listen(getNotificationOnEnter(), get_onEnter(component));
	collector.listen(getNotificationOnExit(), get_onExit(component));

	return collector;
}

}
}

