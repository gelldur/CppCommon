//
// Created by Dawid Drozd aka Gelldur on 11.05.17.
//
#pragma once

#include <cocos2d.h>

inline const cocos2d::Rect& getBoundingBox(cocos2d::CCNode* node)
{
	return node->getBoundingBox();//TODO check is returning by ref
}

inline void registerTouchListener(cocos2d::CCEventListenerTouchOneByOne* listener)
{
	cocos2d::Director::getInstance()->getEventDispatcher()
			->addEventListenerWithSceneGraphPriority(listener, getWorkingNode());//TODO FIXME
}

inline void unregisterTouchListener(cocos2d::CCEventListenerTouchOneByOne* listener)
{
	cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}
