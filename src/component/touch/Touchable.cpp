/*
 * Touchable.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: dawid
 */

#include "Touchable.h"

#include <wrapper.h>

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
		, _collector{nullptr}
{
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = std::bind(&Touchable::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
	_listener->onTouchMoved = std::bind(&Touchable::onTouchMoved, this, std::placeholders::_1, std::placeholders::_2);
	_listener->onTouchCancelled = std::bind(&Touchable::onTouchEnded
											, this
											, std::placeholders::_1
											, std::placeholders::_2);
	_listener->onTouchEnded = std::bind(&Touchable::onTouchEnded, this, std::placeholders::_1, std::placeholders::_2);
}

bool Touchable::onTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	if (isTouched(touch->getLocation()))
	{
		auto bus = getOwner()->getBus();//We need local copy of bus
		bus->notify(TouchBegan{touch});
		return true;
	}

	return false;
}

void Touchable::onTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	getOwner()->getBus()->notify(TouchMoved{touch});
}

void Touchable::onTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	//We need local copy of bus because during notification we can remove self
	auto bus = getOwner()->getBus();
	bus->notify(TouchEnded{touch});
}

void Touchable::onEnter()
{
	registerTouchListener(_listener.get(), _priority);
}

void Touchable::onExit()
{
	unregisterTouchListener(_listener.get());
}

Touchable* Touchable::setMargin(int width, int height)
{
	_widthMargin = width;
	_heightMargin = height;
	return this;
}

void Touchable::addTouchable(cocos2d::CCNode* node)
{
// #ifndef DEBUG
// 	for (auto& element : _touchables)
// 	{
// 		assert(element.get() != node && "Touchable already added!");
// 	}
// #endif

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

Touchable* Touchable::setPriority(int priority)
{
	_priority = priority;
	return this;
}

bool Touchable::isTouched(const cocos2d::CCPoint& worldLocation)
{
	for (const auto& touchable : _touchables)
	{
		if (touchable->isVisible() == false || touchable->isRunning() == false)
		{
			//We skip such touchables. We can touch only things we can see
			continue;
		}

		auto touchBox = getBoundingBox(touchable);
		touchBox.origin.x -= _widthMargin;
		touchBox.size.width += _widthMargin;

		touchBox.origin.y -= _heightMargin;
		touchBox.size.height += _heightMargin;

		if (touchable->getParent() == nullptr)//maybe it is a root!
		{
			touchBox.origin = touchable->convertToWorldSpace({});
		}
		else
		{
			touchBox.origin = touchable->getParent()->convertToWorldSpace(touchBox.origin);
		}

		if (touchBox.containsPoint(worldLocation))
		{
			return true;
		}
	}
	return false;
}

} /* namespace Component */
} /* namespace Dexode */
