/*
 * ComponentManager.h
 *
 *  Created on: Jan 21, 2015
 *      Author: dawid
 */

#pragma once

#include <memory>

#include <base/CCRef.h>

#include <component/Base.h>
#include <Notifier.h>
#include <component/utils/CheckComponentLifeCycle.h>

#include <acme/type_name.h>

namespace cocos2d
{
class Node;
}

namespace Dexode
{
namespace Component
{

template<typename Type>
inline int getIdForType();

class ComponentManager : public cocos2d::Ref
{
public:
	static ComponentManager* create(cocos2d::Node* node)
	{
		auto* ret = new(std::nothrow) ComponentManager();
		if (ret && ret->init(node))
		{
			ret->autorelease();
			return ret;
		}
		else
		{
			delete ret;
			return nullptr;
		}
	}

	static ComponentManager* husk(cocos2d::Node* node);

	virtual ~ComponentManager();

	ComponentManager* init(cocos2d::Node* node);

	template<class T, typename ... Args>
	int addComponent(Args&& ... params)
	{
		return addComponent(std::unique_ptr<Base>(new T(std::forward<Args>(params)...)));
	}

	template<class T>
	int addComponent(std::unique_ptr<T> component)
	{
		static_assert(std::is_base_of<Base, T>::value, "T must inherit from Component");
		assert(hasComponent<T>() == false && "You already added such component");
#ifdef DEBUG
		assert(_lock == false && "Can't add objects during lock");
#endif

		auto componentRaw = component.get();

		const int tag = getIdForType<T>();
		_components.emplace(tag, std::move(component));
		componentRaw->setOwner(this);
		componentRaw->onAttach();

		return tag;
	}

	template<class T>
	void removeComponent()
	{
#ifdef DEBUG
		assert(_lock == false && "Can't remove objects during lock");
#endif
		const int tag = getIdForType<T>();
		auto element = _components.find(tag);

		if (element == _components.end())
		{
			return;//No such component
		}

		auto component = std::move(element->second);
		_components.erase(element);
		component->onDetach();
		component->setOwner(nullptr);
	}

	const std::shared_ptr<Notifier>& getBus()
	{
		return _bus;
	}

	template<class T>
	bool hasComponent()
	{
		const int tag = getIdForType<T>();
		auto element = _components.find(tag);

		return element != _components.end();
	}

	template<class T>
	T* getComponent()
	{
		const int tag = getIdForType<T>();
		auto element = _components.find(tag);

		if (element == _components.end())
		{
			return nullptr;
		}
		return dynamic_cast<T*>(element->second.get());
	}

	cocos2d::Node* getWorkingNode()
	{
		assert(_workingNode);
		return _workingNode;
	}

private:
#ifdef DEBUG
	bool _lock = false;
#endif
	cocos2d::Node* _workingNode = nullptr;
	std::shared_ptr<Notifier> _bus;
	std::map<int, std::unique_ptr<Base>> _components;

	ComponentManager();
};

inline int _UniqueComponentIdNonDeterministic()
{
	static int id = 5001;
	return ++id;
}

template<typename Type>
inline int getIdForType()
{
	static const int id_for_type = _UniqueComponentIdNonDeterministic();
	return id_for_type;
}

}
/* namespace Component */
} /* namespace Dexode */
