/*
 * ComponentManager.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: dawid
 */

#include "ComponentManager.h"
#include <cocos2d.h>
#include <component/common/LifeCycle.h>

namespace Dexode
{
namespace Component
{

ComponentManager::ComponentManager()
		: _bus{std::make_shared<Notifier>()}
{
}

ComponentManager::~ComponentManager()
{
#ifdef DEBUG
	//We lock Manager
	_lock = true;
#endif
	for (auto& element : _components)
	{
		element.second->onDetach();
	}
}

ComponentManager* ComponentManager::init(cocos2d::Node* node)
{
	_workingNode = node;
	addComponent<LifeCycle>();//TODO issues occurs when node was added previously
	return this;
}

ComponentManager* ComponentManager::husk(cocos2d::Node* node)
{
	auto manager = dynamic_cast<ComponentManager*>(node->getUserObject());
	assert(manager != nullptr && "This node doesn't have component manager or it was removed!");
	return manager;
}

} /* namespace Component */
} /* namespace Dexode */

