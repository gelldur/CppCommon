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

	void addEventListenerWithSceneGraphPriority(cocos2d::EventListener* listener, cocos2d::Node* node);

	void listen(const std::string& event, const std::function<void(cocos2d::EventCustom*)>& listener);
	void unlisten(const std::string& event);
	void unlistenAll();

private:
	std::map<std::string, cocos2d::EventListener*> _listeners;
	std::map<void*, cocos2d::EventListener*> _listenersForTarget;
};

}
