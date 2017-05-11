//
// Created by Dawid Drozd aka Gelldur on 13/11/16.
//

#include "LifeCycle.h"

#include <wrapper.h>

#include <component/ComponentManager.h>
#include <component/common/LifeCycleEvents.h>

namespace Dexode
{
namespace Component
{

struct DummyNode : public cocos2d::Node
{
	using inherited = cocos2d::Node;

	virtual void onEnter() override
	{
		inherited::onEnter();
		if (onEnterCallback)
		{
			onEnterCallback();
		}
	}

	virtual void onExit() override
	{
		inherited::onExit();
		if (onExitCallback)
		{
			onExitCallback();
		}
	}

	std::function<void()> onEnterCallback;
	std::function<void()> onExitCallback;
};

LifeCycle::LifeCycle()
		: _dummyNode(new DummyNode{})
{
}

LifeCycle::~LifeCycle()
{
	assert(_dummyNode->getParent() == nullptr);
	CC_SAFE_DELETE(_dummyNode);
}

void LifeCycle::onAttach()
{
	inherited::onAttach();

	auto helperNode = static_cast<DummyNode*>(_dummyNode);
	helperNode->onEnterCallback = std::bind(&LifeCycle::onEnterNode, this);
	helperNode->onExitCallback = std::bind(&LifeCycle::onExitNode, this);

	getWorkingNode()->addChild(_dummyNode);
}

void LifeCycle::onDetach()
{
	auto helperNode = static_cast<DummyNode*>(_dummyNode);
	helperNode->onEnterCallback = {};
	helperNode->onExitCallback = {};

	getWorkingNode()->removeChild(_dummyNode, false);

	inherited::onDetach();
}

void LifeCycle::onEnterNode()
{
	getOwner()->getBus()->notify(getNotificationOnEnter());
}

void LifeCycle::onExitNode()
{
	getOwner()->getBus()->notify(getNotificationOnExit());
}

}
}
