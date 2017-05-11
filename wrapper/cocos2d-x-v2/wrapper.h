//
// Created by Dawid Drozd aka Gelldur on 11.05.17.
//
#pragma once

#include <cocos2d.h>
#include <EventTouchListener.h>

inline const cocos2d::CCRect getBoundingBox(cocos2d::CCNode* node)
{
	return node->boundingBox();
}

inline void registerTouchListener(cocos2d::EventListenerTouchOneByOne* listener)
{
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(listener, 0, true);
}

inline void unregisterTouchListener(cocos2d::EventListenerTouchOneByOne* listener)
{
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(listener);
}
