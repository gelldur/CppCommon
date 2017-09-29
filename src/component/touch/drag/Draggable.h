/*
 * Dragable.h
 *
 *  Created on: Jan 24, 2015
 *      Author: dawid
 */

#pragma once

#include <functional>

#include <Vec.h>

#include <component/Base.h>
#include <eventbus/EventCollector.h>

#include <predeclare.h>

namespace Dexode
{
namespace Component
{

class ComponentManager;

template<class T>
class RegisterTouch;

struct OnDragEvent;

class Draggable : public Base
{
	using inherited = Base;
public:
	using OnTouch = std::function<void(OnDragEvent)>;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onTouchBegan(cocos2d::CCTouch* touch);
	void onTouchMoved(cocos2d::CCTouch* touch);
	void onTouchEnded(cocos2d::CCTouch* touch);

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
	EventCollector _collector = nullptr;
};

} /* namespace Component */
} /* namespace Dexode */
