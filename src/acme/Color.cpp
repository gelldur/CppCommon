//
// Created by Dawid Drozd aka Gelldur on 14.05.17.
//
#include "Color.h"

namespace Color
{
cocos2d::ccColor3B convertTo3B(const int color)
{
	cocos2d::ccColor3B converted;
	converted.r = getRed(color);
	converted.g = getGreen(color);
	converted.b = getBlue(color);
	return converted;
}

cocos2d::ccColor4F convertTo4F(const int color)
{
	cocos2d::ccColor4F converted;
	converted.r = getRed(color) / 255.F;
	converted.g = getGreen(color) / 255.F;
	converted.b = getBlue(color) / 255.F;
	converted.a = getAlpha(color) / 255.F;
	return converted;
}

cocos2d::ccColor4B convertTo4B(const int color)
{
	cocos2d::ccColor4B converted;
	converted.r = getRed(color);
	converted.g = getGreen(color);
	converted.b = getBlue(color);
	converted.a = getAlpha(color);
	return converted;
}

}
