//
// Created by Dawid Drozd aka Gelldur on 8/30/16.
//

#include "EventListener.h"

#include <cocos2d.h>

#include <exception/Fail.h>

namespace Dexode
{

EventListener::~EventListener()
{
	unlistenAll();
}

void EventListener::listen(const std::string& event, const std::function<void(cocos2d::EventCustom*)>& listener)
{
	if (_listeners.find(event) != _listeners.end())
	{
		Fail(__FILE__, __func__, __LINE__).add("First unlisten!").report();
	}

	auto eventListener = cocos2d::Director::getInstance()->getEventDispatcher()
			->addCustomEventListener(event, listener);
	_listeners[event] = eventListener;
}

void EventListener::unlisten(const std::string& event)
{
	auto found = _listeners.find(event);
	if (found == _listeners.end())
	{
		//WLOG("Already unlisten");
		return;
	}

	cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(found->second);
	_listeners.erase(event);
}

void EventListener::unlistenAll()
{
	for (auto& listener : _listeners)
	{
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener.second);
	}
	_listeners.clear();
	for (auto& listener : _listenersForTarget)
	{
		cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(listener.second);
	}
	_listenersForTarget.clear();
}

void EventListener::addEventListenerWithSceneGraphPriority(cocos2d::EventListener* listener, cocos2d::Node* node)
{
	if (_listenersForTarget.find(node) != _listenersForTarget.end())
	{
		Fail(__FILE__, __func__, __LINE__).add("First unlisten!").report();
	}
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
	_listenersForTarget[node] = listener;
}

}
