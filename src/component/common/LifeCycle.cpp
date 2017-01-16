//
// Created by Dawid Drozd aka Gelldur on 13/11/16.
//

#include "LifeCycle.h"

#include <2d/CCNode.h>

#include <component/ComponentManager.h>
#include <component/common/LifeCycleEvents.h>

namespace Dexode
{
namespace Component
{

void LifeCycle::onAttach()
{
	inherited::onAttach();
	getWorkingNode()->setOnEnterCallback(std::bind(&LifeCycle::onEnterNode, this));
	getWorkingNode()->setOnExitCallback(std::bind(&LifeCycle::onExitNode, this));
}

void LifeCycle::onDetach()
{
	//Using working node when it is destroyed //autorelease
	//	getWorkingNode()->setOnEnterCallback({});//Remove callbacks
	//	getWorkingNode()->setOnExitCallback({});
	inherited::onDetach();
}

void LifeCycle::onEnterNode()
{
	getOwner()->getBus()->notify(getNotificationOnEnter());
}

void LifeCycle::onExitNode()
{
	getOwner()->getBus()->notify(getNotificationOnExit());
}

}
}
