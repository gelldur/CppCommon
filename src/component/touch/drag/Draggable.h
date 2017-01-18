/*
 * Dragable.h
 *
 *  Created on: Jan 24, 2015
 *      Author: dawid
 */

#pragma once

#include <functional>

#include <math/Vec2.h>

#include <component/Base.h>
#include <EventCollector.h>

namespace cocos2d
{
class Touch;

class Node;
}

namespace Dexode
{
namespace Component
{

class ComponentManager;

template<class T>
class RegisterTouch;

class OnDragEvent;

class Draggable : public Base
{
	using inherited = Base;
public:
	using OnTouch = std::function<void(OnDragEvent)>;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onTouchBegan(cocos2d::Touch* touch);
	void onTouchMoved(cocos2d::Touch* touch);
	void onTouchEnded(cocos2d::Touch* touch);

	void setListenerTouchBegan(const OnTouch& onTouchBegan);
	void setListenerTouchMoved(const OnTouch& onTouchMoved);
	void setListenerTouchEnded(const OnTouch& onTouchEnded);
	void setListeners(const OnTouch& onTouchBegan, const OnTouch& onTouchMoved, const OnTouch& onTouchEnded);

	void setFlags(int flags);

private:
	cocos2d::Vec2 _startPosition;
	cocos2d::Vec2 _offset;

	int _flags = 0;

	OnTouch _onTouchBegan;
	OnTouch _onTouchMoved;
	OnTouch _onTouchEnded;
	EventCollector _collector;
};

} /* namespace Component */
} /* namespace Dexode */
