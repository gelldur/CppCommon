/*
 * Touchable.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: dawid
 */

#include "Touchable.h"

#include <cocos2d.h>

#include <component/ComponentManager.h>

#include <component/touch/TouchableEvents.h>
#include <component/common/LifeCycleEvents.h>

USING_NS_CC;

namespace Dexode
{
namespace Component
{

Touchable::Touchable()
		: _listener(EventListenerTouchOneByOne::create())
{
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(Touchable::onTouchBegan, this);
	_listener->onTouchMoved = CC_CALLBACK_2(Touchable::onTouchMoved, this);
	_listener->onTouchCancelled = CC_CALLBACK_2(Touchable::onTouchEnded, this);
	_listener->onTouchEnded = CC_CALLBACK_2(Touchable::onTouchEnded, this);
}

bool Touchable::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	for (const auto& touchable : _touchables)
	{
		if (touchable->isVisible() == false || touchable->isRunning() == false)
		{
			//We skip such touchables. We can touch only things we can see
			continue;
		}

#ifdef DEBUG
		auto& children = getWorkingNode()->getChildren();
		bool found = (touchable.get() == getWorkingNode());
		for (auto&& child : children)
		{
			if (child == touchable.get())
			{
				found = true;
				break;
			}
		}
		assert(found && "Child not found! Maybe you shouldn't track this child");
#endif

		auto touchBox = touchable->getBoundingBox();
		touchBox.origin.x -= _widthMargin;
		touchBox.size.width += _widthMargin;

		touchBox.origin.y -= _heightMargin;
		touchBox.size.height += _heightMargin;

		touchBox.origin = touchable->getParent()->convertToWorldSpace(touchBox.origin);

		if (touchBox.containsPoint(touch->getLocation()))
		{
			getOwner()->getBus()->notify(getNotificationTouchBegan(), touch);
			return true;
		}
	}

	return false;
}

void Touchable::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	getOwner()->getBus()->notify(getNotificationTouchMoved(), touch);
}

void Touchable::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	getOwner()->getBus()->notify(getNotificationTouchEnded(), touch);
}

void Touchable::onEnter()
{
	Director::getInstance()->getEventDispatcher()
			->addEventListenerWithSceneGraphPriority(_listener.get(), getWorkingNode());
}

void Touchable::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(_listener.get());
}

Touchable* Touchable::setMargin(int width, int height)
{
	_widthMargin = width;
	_heightMargin = height;
	return this;
}

void Touchable::addTouchable(cocos2d::Node* node)
{
	assert((node == getWorkingNode() || node->getParent() == getWorkingNode()) && "Node should be a child of _node");
#ifndef DEBUG
	for (auto& element : _touchables)
	{
		assert(element.get() != node && "Touchable already added!");
	}
#endif

	_touchables.emplace_back(node);
}

void Touchable::onAttach()
{
	inherited::onAttach();
	_collector = listenForOnEnterOnExit(this);
}

void Touchable::onDetach()
{
	_collector.unlistenAll();
	inherited::onDetach();
}

} /* namespace Component */
} /* namespace Dexode */
