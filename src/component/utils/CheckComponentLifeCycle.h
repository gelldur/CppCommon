//
// Created by Dawid Drozd aka Gelldur on 10/11/16.
//

#pragma once

#include <type_traits>

#include <predeclare.h>

namespace Dexode
{
namespace Tama
{
namespace Component
{
class ComponentManager;
}
}
}

template<typename T>
struct check_onAttach
{
private:
	template<typename U>
	static auto test(int) -> decltype(std::declval<U>().onAttach(), std::true_type{});

	template<typename>
	static std::false_type test(...);

public:
	static const bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template<typename T>
struct check_onDetach
{
private:
	template<typename U>
	static auto test(int) -> decltype(std::declval<U>().onDetach(), std::true_type{});

	template<typename>
	static std::false_type test(...);

public:
	static const bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template<class T>
typename std::enable_if<check_onAttach<T>::value>::type
onAttach(T* component, cocos2d::Node* workingNode, Dexode::Tama::Component::ComponentManager* componentManager)
{
	component->onAttach(workingNode, componentManager);
}

template<class T>
typename std::enable_if<!check_onAttach<T>::value>::type
onAttach(T* component
		, cocos2d::Node* workingNode
		, Dexode::Tama::Component::ComponentManager* componentManager)//Do nothing
{
}

template<class T>
typename std::enable_if<check_onDetach<T>::value>::type
onDetach(T* component, cocos2d::Node* workingNode, Dexode::Tama::Component::ComponentManager* componentManager)
{
	component->onDetach(workingNode, componentManager);
}

template<class T>
typename std::enable_if<!check_onDetach<T>::value>::type
onDetach(T* component
		, cocos2d::Node* workingNode
		, Dexode::Tama::Component::ComponentManager* componentManager)//Do nothing
{
}
