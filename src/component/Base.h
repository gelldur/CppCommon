//
// Created by Dawid Drozd aka Gelldur on 10/11/16.
//

#pragma once

#include <predeclare.h>

namespace Dexode
{
namespace Component
{

class ComponentManager;

class Base
{
public:
	friend class ComponentManager;

	virtual ~Base() = default;

	virtual void onAttach();

	virtual void onDetach()
	{
		_owner = nullptr;
	}

	Dexode::Component::ComponentManager* getOwner()
	{
		return _owner;
	}

	cocos2d::CCNode* getWorkingNode();

protected:
	void setOwner(Dexode::Component::ComponentManager* owner)
	{
		_owner = owner;
	}

private:
	ComponentManager* _owner;
};

}
}
