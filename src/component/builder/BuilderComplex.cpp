/*
 * BuilderComplex.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: dawid
 */
#include "BuilderComplex.h"

#include "pet/lua/LuaNotifier.h"

namespace Dexode
{
namespace Component
{

BuilderComplex& BuilderComplex::addBehaviourButton(const std::string& notification)
{

	addBehaviourButton([notification](cocos2d::Touch* touch)
					   {
						   getLuaNotifier().notify(getNotification(notification), "");
					   });

	return *this;
}

}
}
