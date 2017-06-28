//
// Created by Dawid Drozd aka Gelldur on 19.06.17.
//
#include "RedDot.h"
//////////////////////////////////

#include <acme/Color.h>

namespace Debug
{

bool RedDot::init(float radius, int color)
{
	if (inherited::init() == false)
	{
		return false;
	}

	drawDot(cocos2d::CCPoint{0, 0}, radius, Color::convertTo4F(color));
	setZOrder(INT_MAX);
	return true;
}

RedDot* RedDot::show(cocos2d::CCPoint worldPosition, float radius)
{
	auto dot = create(radius);
	dot->setPosition(worldPosition);

	cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(dot);

	return dot;
}

}
