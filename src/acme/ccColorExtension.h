//
// Created by Dawid Drozd aka Gelldur on 14.05.17.
//
#pragma once

#include <ccTypes.h>

//Color.h is placed in common-cpp repositiory: https://github.com/gelldur/common-cpp
#include <acme/Color.h>

namespace Acme
{

namespace Color
{

cocos2d::ccColor3B convertTo3B(const int colorARGB);
cocos2d::ccColor4F convertTo4F(const int colorARGB);
cocos2d::ccColor4B convertTo4B(const int colorARGB);

template<>
inline convert::operator cocos2d::ccColor3B() const
{
	return convertTo3B(_color);
}

template<>
inline convert::operator cocos2d::ccColor4F() const
{
	return convertTo4F(_color);
}

template<>
inline convert::operator cocos2d::ccColor4B() const
{
	return convertTo4B(_color);
}

}
}
