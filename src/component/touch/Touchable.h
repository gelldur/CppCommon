/*
 * Touchable.h
 *
 *  Created on: Jan 24, 2015
 *      Author: dawid
 */

#pragma once

#include <vector>

#include <base/CCEventListenerTouch.h>

#include <component/Base.h>
#include <memory/RefHolder.h>
#include <EventCollector.h>

namespace cocos2d
{
class Node;

class Touch;

class Event;
}

namespace Dexode
{
namespace Component
{

class ComponentManager;

class Touchable : public Base
{
	using inherited = Base;
public:
	Touchable();

	virtual void onAttach() override;
	virtual void onDetach() override;

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onEnter();

	void onExit();

	Touchable* setMargin(int width, int height);

	void addTouchable(cocos2d::Node* node);

private:
	int _widthMargin = 0;
	int _heightMargin = 0;
	RefHolder<cocos2d::EventListenerTouchOneByOne> _listener;
	EventCollector _collector;

	std::vector<RefHolder<cocos2d::Node>> _touchables;
};

} /* namespace Component */
} /* namespace Dexode */
