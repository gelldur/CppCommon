//
// Created by Dawid Drozd aka Gelldur on 8/30/16.
//

#pragma once

#include <map>
#include <string>
#include <functional>

namespace cocos2d
{
class EventCustom;

class EventListener;

class Node;
}

namespace Dexode
{

class EventListener
{
public:
	~EventListener();

	void addEventListenerWithSceneGraphPriority(cocos2d::CCEventListener* listener, cocos2d::CCNode* node);

	void listen(const std::string& event, const std::function<void(cocos2d::CCEventCustom*)>& listener);
	void unlisten(const std::string& event);
	void unlistenAll();

private:
	std::map<std::string, cocos2d::CCEventListener*> _listeners;
	std::map<void*, cocos2d::CCEventListener*> _listenersForTarget;
};

}
