/*
 * Touchable.h
 *
 *  Created on: Jan 24, 2015
 *      Author: dawid
 */

#pragma once

#include <vector>

#include <EventTouchListener.h>

#include <component/Base.h>
#include <memory/RefHolder.h>
#include <eventbus/EventCollector.h>

#include <predeclare.h>

namespace Dexode
{
namespace Component
{

class Touchable : public Base
{
	using inherited = Base;
public:
	Touchable();

	virtual void onAttach() override;
	virtual void onDetach() override;

	bool isTouched(const cocos2d::CCPoint& worldLocation);

	bool onTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	void onTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	void onTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

	void onEnter();

	void onExit();

	Touchable* setMargin(int width, int height);
	Touchable* setPriority(int priority);

	void addTouchable(cocos2d::CCNode* node);

private:
	int _widthMargin = 0;
	int _heightMargin = 0;
	int _priority = 0;
	RefHolder<cocos2d::EventListenerTouchOneByOne> _listener;
	EventCollector _collector;

	std::vector<RefHolder<cocos2d::CCNode>> _touchables;
};

} /* namespace Component */
} /* namespace Dexode */
