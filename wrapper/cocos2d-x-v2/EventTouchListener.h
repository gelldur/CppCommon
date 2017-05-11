//
// Created by Dawid Drozd aka Gelldur on 11.05.17.
//
#pragma once

#include <functional>

#include <touch_dispatcher/CCTouch.h>
#include <touch_dispatcher/CCTouchHandler.h>

namespace cocos2d
{

class TouchWrapper
		: public cocos2d::CCObject
		  , public cocos2d::CCTargetedTouchDelegate
{
public:
	static TouchWrapper* create()
	{
		TouchWrapper* pRet = new TouchWrapper();
		if (pRet)
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return NULL;
		}
	}

	void setSwallowTouches(bool dummy)//dummy method
	{
	}

	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) override
	{
		return onTouchBegan(pTouch, pEvent);
	}

	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) override
	{
		onTouchMoved(pTouch, pEvent);
	}

	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) override
	{
		onTouchEnded(pTouch, pEvent);
	}

	virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent) override
	{
		onTouchCancelled(pTouch, pEvent);
	}

	std::function<bool(cocos2d::CCTouch*, cocos2d::CCEvent*)> onTouchBegan;
	std::function<void(cocos2d::CCTouch*, cocos2d::CCEvent*)> onTouchMoved;
	std::function<void(cocos2d::CCTouch*, cocos2d::CCEvent*)> onTouchCancelled;
	std::function<void(cocos2d::CCTouch*, cocos2d::CCEvent*)> onTouchEnded;
};

using EventListenerTouchOneByOne = TouchWrapper;
}