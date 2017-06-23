//
// Created by Dawid Drozd aka Gelldur on 19.06.17.
//
#pragma once

#include <cocos2d.h>

namespace Debug
{

//TODO Add debugable grid on screen

class RedDot : public cocos2d::CCDrawNode
{
	using inherited = cocos2d::CCDrawNode;
public:
	static RedDot* create(float radius = 4, int color = 0xffff0000)
	{
		RedDot* ret = new(std::nothrow) RedDot();
		if (ret && ret->init(radius, color))
		{
			ret->autorelease();
			return ret;
		}
		else
		{
			delete ret;
			return nullptr;
		}
	}

	static RedDot* show(cocos2d::CCPoint worldPosition, float radius = 4);

	bool init(float radius, int color = 0xffff0000);
};

}
