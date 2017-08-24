//
// Created by Dawid Drozd aka Gelldur on 14.05.17.
//
#include "ccColorExtension.h"

namespace Acme
{
namespace Color
{

cocos2d::ccColor3B convertTo3B(const int color)
{
	cocos2d::ccColor3B converted;
	converted.r = Acme::Color::ARGB::getRed(color);
	converted.g = Acme::Color::ARGB::getGreen(color);
	converted.b = Acme::Color::ARGB::getBlue(color);
	return converted;
}

cocos2d::ccColor4F convertTo4F(const int color)
{
	cocos2d::ccColor4F converted;
	converted.r = Acme::Color::ARGB::getRed(color) / 255.F;
	converted.g = Acme::Color::ARGB::getGreen(color) / 255.F;
	converted.b = Acme::Color::ARGB::getBlue(color) / 255.F;
	converted.a = Acme::Color::ARGB::getAlpha(color) / 255.F;
	return converted;
}

cocos2d::ccColor4B convertTo4B(const int color)
{
	cocos2d::ccColor4B converted;
	converted.r = Acme::Color::ARGB::getRed(color);
	converted.g = Acme::Color::ARGB::getGreen(color);
	converted.b = Acme::Color::ARGB::getBlue(color);
	converted.a = Acme::Color::ARGB::getAlpha(color);
	return converted;
}

}
}
